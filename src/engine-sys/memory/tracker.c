#include<wh/debug/exceptions.h>
#include<wh/debug/logger.h>
#include<wh-sys/memory.h>

#include<stdlib.h>
// Linked list tracking

typedef struct {
	void** owner;
	u64 line;
	const char* file;
} _wh_heap_ptr_pair_s;

typedef struct _wh_heap_list_entry {
	u64 owner_count;
	_wh_heap_ptr_pair_s* owners;
	
	void* ptr;
	void* heap;

	struct _wh_heap_list_entry* next;
	struct _wh_heap_list_entry* previous;
} _wh_heap_list_entry_s;

typedef struct {
	wh_atomic_lock_s lock;
	_wh_heap_list_entry_s* nodes;
	_wh_heap_list_entry_s* last;
} _wh_heap_list_s;

static _wh_heap_list_s _list = { 0 };

extern void* _wh_alloc_no_tracking(_wh_mem_alloc_params params);
extern void _wh_free_no_tracking(_wh_mem_free_params params);
extern void* _wh_realloc_no_tracking(_wh_mem_realloc_params params);

/*
 * Tracking functions
 *
 */
void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file) {
	_wh_heap_list_entry_s* last = nullptr;
	_wh_heap_ptr_pair_s* owners = nullptr;

	if (nullptr == ptr) {
		return;
	}

	if (nullptr == owner) {
		wh_log_critical(("Untracked pointer at [ %s:%u ]!"), file, line);
		return;
	}

	if (nullptr == _list.nodes) {
		_list.nodes = calloc(1, sizeof(_wh_heap_list_entry_s));
		_list.last = _list.nodes;

		if (nullptr == _list.nodes) {
			wh_log_error(("Failed to allocate memory"));
			return;
		}

		last = _list.last;
	} else {
		last = _list.last;
		last->next = calloc(1, sizeof(_wh_heap_list_entry_s));

		if (nullptr == last->next) {
			wh_log_error(("Failed to allocate memory"));
			return;
		}

		// shuffling the nodes
		last->next->previous = last;
		_list.last = last->next;
		last = last->next;
	}

	last->ptr = ptr;
	last->heap = heap;
	last->owner_count = 0;

	owners = realloc(last->owners, sizeof(_wh_heap_ptr_pair_s) * (last->owner_count + 1));

	if (nullptr == owners) {
		wh_log_error(("Failed to allocate memory"));
		return;
	}

	last->owners = owners;

	owners[last->owner_count].owner = owner;
	owners[last->owner_count].line = line;
	owners[last->owner_count].file = file;
	last->owner_count += 1;

	wh_log_debug(("inserted new node!"));
}

void _wh_tracker_remove(void* owner, void* ptr) {
	wh_spinlock_v2(&_list.lock) {
		_wh_heap_list_entry_s* current = _list.nodes;

		if (nullptr == current) {
			return;
		}

		while (ptr != current->ptr) {
			current = current->next;

			if (nullptr == current) {
				return;
			}
		}

		switch (current->owner_count) {
			case 1:
				wh_log_error(("Disowning tracked pointer!"));

				if (nullptr != current->previous) { 
					wh_log_debug(("Previous node is not null assigning next"));
					current->previous->next = current->next;
				} else {
					wh_log_debug(("Previous node is null assigning to first object"));
					_list.nodes = current->next;
				}

				if (current->next) {
					current->next->previous = current->previous;
				} else {
					_list.last = current->previous;
				}

				free(current->owners);
				free(current);
				break;

			default:
				wh_log_debug(("Clearing owner!"));
				wh_for(u64, i, current->owner_count) {
					if (owner == current->owners[i].owner) {
						current->owner_count--;
						current->owners[i].owner = current->owners[current->owner_count].owner;
						current->owners[i].file = current->owners[current->owner_count].file;
						current->owners[i].line = current->owners[current->owner_count].line;
						current->owners = realloc(current->owners, sizeof(_wh_heap_ptr_pair_s) * current->owner_count);
						break;
					}
				}
		}
	}
}

i64 _wh_mem_scan(void) {
	i64 count = 0;
	_wh_heap_list_entry_s* current = _list.nodes;

	wh_spinlock_v2(&_list.lock) {
		while (nullptr != current) {
			wh_log_debug(("Node found! [ %u ] next is [ %u ]"), current->ptr, current->next);

			wh_for(u64, i, current->owner_count) {
				bool clean_up = false;

				if (nullptr == current->owners[i].owner) {
					continue;
				}

				wh_try {
					if (*current->owners[i].owner != current->ptr) {
						wh_log_warning(("Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
						clean_up = true;
					}
				} wh_catch(ex) {
					wh_log_critical(("SEGFAULT :: Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
					clean_up = true;
				}

				if ( clean_up) {
					current->owners[i].owner = current->owners[current->owner_count].owner;
					current->owners[i].line = current->owners[current->owner_count].line;
					current->owners[i].file = current->owners[current->owner_count].file;
					current->owner_count--;
					current->owners = realloc(current->owners, sizeof(_wh_heap_ptr_pair_s) * current->owner_count);
				}
			}

			if (0 == current->owner_count) {
				count++;
				wh_log_error(("LEAK FOUND! freeing... ptr : [ %u ]"), current->ptr);
				wh_free(current->heap, current->ptr, nullptr);
			}

			current = current->next;
		}
	}

	//usleep(100);
	return count;
}

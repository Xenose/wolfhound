#include<wh/debug/exceptions.h>
#include<wh/debug/logger.h>
#include<wh-sys/memory.h>
#include<wh-data/list.h>

#include<stdlib.h>
// Linked list tracking

typedef struct {
	void* ptr;
	void** owners;
	u64 owner_count;
	u64 line;
	const char* file;
} _wh_heap_ptr_pair_s;

//static _wh_heap_list_s _list = { 0 };

extern void* _wh_alloc_no_tracking(_wh_mem_alloc_params params);
extern void _wh_free_no_tracking(_wh_mem_free_params params);
extern void* _wh_realloc_no_tracking(_wh_mem_realloc_params params);

static wh_list_s _list = {
	.stype = WH_STRUCT_TYPE_LLIST_STD_DOUBLE,
	.type_size = sizeof(_wh_heap_ptr_pair_s),
};

bool _wh_track_search(void* entry_in, void* ptr_in) {
	_wh_heap_ptr_pair_s* entry = entry_in;

	if (entry->ptr == ptr_in) {
		return true;
	}

	return false;
}

/*
 * Tracking functions
 *
 */
void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file) {
	_wh_heap_ptr_pair_s* entry = nullptr;

	if (nullptr == ptr) {
		return;
	}

	if (nullptr == owner) {
		wh_log_critical(("Untracked pointer at [ %s:%u ]!"), file, line);
	}

	entry = wh_list_search_func(&_list, ptr, &_wh_track_search);

	if (nullptr == entry) {
		_wh_heap_ptr_pair_s tmp = {
			.ptr = ptr,
			.owners = malloc(sizeof(void*)),
			.owner_count = 1,
			.line = line,
			.file = file,
		};

		if (nullptr == tmp.owners) {
			wh_log_critical(("Failed to allocate owner ptr memory"));
		} else {
			tmp.owners[0] = owner;
		}

		wh_list_push_back(&_list, &tmp);
	} else {
		void** tmp = realloc(entry->owners, sizeof(void*) * (entry->owner_count + 1));

		if (nullptr == tmp) {
			wh_log_critical(("Failed to allocate owner ptr memory"));
		} else {
			entry->owners = tmp;
			entry->owners[entry->owner_count] = owner;
		}

		++entry->owner_count;
	}

	wh_log_debug(("inserted new node!"));
}

void _wh_tracker_remove(void* owner, void* ptr) {
	u64 index = 0;
	_wh_heap_ptr_pair_s* entry = nullptr;

	if (nullptr == ptr) {
		return;
	}

	if (nullptr == owner) {
		wh_log_critical(("Freeing untracked pointer!"));
	}

	entry = wh_list_search_func(&_list, ptr, &_wh_track_search, &index);

	if (nullptr != entry) {
		wh_for(u64, i, entry->owner_count) {
			if (owner == entry->owners[i]) {
				--entry->owner_count;
				entry->owners[i] = entry->owners[entry->owner_count];
				break;
			}
		}

		if (0 == entry->owner_count) {
			wh_list_delete(&_list, index);
		}
	}
}

void _wh_mem_scan_for_each(void* node, u64 index) {
	bool clean_up = false;
	_wh_heap_ptr_pair_s* entry = node;

	wh_for(u64, i, entry->owner_count) {
		wh_try {
			if (entry->owners[i] != entry->ptr) {
				//wh_log_warning(("Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
				clean_up = true;
			}
		} wh_catch(ex) {
			//wh_log_critical(("SEGFAULT :: Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
			clean_up = true;
		}

		if (clean_up) {
			wh_log_error(("Found a loss end pointer, clean up your mess!"));
			--entry->owner_count;
			entry->owners[i] = entry->owners[entry->owner_count];
		}
	}

	if (0 == entry->owner_count) {
		wh_log_error(("LEAK FOUND! freeing... ptr : [ %u ]"), entry->ptr);
		//wh_free(->heap, current->ptr, nullptr);
	}
}

i64 _wh_mem_scan(void) {
	i64 count = 0;

	wh_list_for_each(&_list, &_wh_mem_scan_for_each);


	/*_wh_heap_list_entry_s* current = _list.nodes;

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
	}*/

	//usleep(100);
	return count;
}

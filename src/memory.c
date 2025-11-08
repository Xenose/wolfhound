#include<stdlib.h>
#include<string.h>
#include<stdatomic.h>
#include<errno.h>


// my stuff
#include<wh/debug/logger.h>
#include<wh/memory.h>
#include<wh/sys/memory.h>
#include<wh/maths/memory.h>
#include<wh/maths/core.h>

#include<wh/memory/arena.h>
#include<wh/memory/freelist.h>

#include<wh/wrap/unistd.h>

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
	atomic_flag lock;
	_wh_heap_list_entry_s* nodes;
	_wh_heap_list_entry_s* last;
} _wh_heap_list_s;

static _wh_heap_list_s _list = { 0 };

// hashmap

typedef struct {
	wh_heap_header_s* header;
	const char* name;
} _wh_heap_entry_s;

typedef struct {
	atomic_flag lock;
	u64 count;
	u64 used;
	_wh_heap_entry_s* entries;
} _wh_heap_table_s;

static _wh_heap_table_s _table = { 0 };

// the global main heap
static wh_heap_header_s* _heap_main;

// allocation functions
void  (*_wh_free)(_wh_mem_free_params params) = nullptr;
void* (*_wh_alloc)(_wh_mem_alloc_params params) = nullptr;
void* (*_wh_realloc)(_wh_mem_realloc_params params) = nullptr;

/*
 * Tracking functions
 *
 */
static void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file) {
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
		last->ptr = ptr;
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

	owners = realloc(last->owners, sizeof(_wh_heap_ptr_pair_s));

	if (nullptr == owners) {
		wh_log_error(("Failed to allocate memory"));
		return;
	}

	last->owners = owners;

	owners[last->owner_count].owner = owner;
	owners[last->owner_count].line = line;
	owners[last->owner_count].file = file;
	last->owner_count = 1;

	wh_log_debug(("inserted new node!"));
}

static void _wh_tracker_remove(void* owner, void* ptr) {
	_wh_heap_list_entry_s* current = _list.nodes;

	while (ptr != current->ptr) {
		current = current->next;

		if (nullptr == current) {
			return;
		}
	}

	switch (current->owner_count) {
		case 0:
			wh_log_debug(("Ereasing tracked pointer!"));

			if (nullptr != current->previous) { 
				current->previous->previous = current->next;
			} else {
				_list.nodes = current->next;
			}


			free(current->owners);
			free(current);
			break;

		default:
			--current->owner_count;
			wh_log_debug(("Clearing owner!"));

			wh_for(u64, i, current->owner_count) {
				if (nullptr == owner) {
					continue;
				}

				if (owner == current->owners[i].owner) {
					current->owners[i].owner = current->owners[current->owner_count].owner;
					current->owners[i].file = current->owners[current->owner_count].file;
					current->owners[i].line = current->owners[current->owner_count].line;
				}
			}
	}
}

/*
 * Hashmap functions
 *
 */
wh_heap_header_s* wh_heap_insert(const char* name, wh_heap_header_s* header) {
	i64 hash = 0;
	u64 retry = 0;
	u64 page_size = 0;
	_wh_heap_entry_s* entry = nullptr;

	wh_log_debug(("Inserting new entry named [ %s ]"), name);

	wh_spin_lock(&_table.lock) {
		if (_table.used >= _table.count) {
		go_realloc:
			wh_log_debug(("Expanding table"));
			_wh_heap_entry_s* new_entries = nullptr;

			if (3 <= retry++) {
				wh_log_critical(("Failed to realloc hashmap table!"));
				wh_spin_lock_goto(&_table.lock, go_error_exit);
			}

			page_size += (u64)getpagesize();

			u64 new_size = (_table.count * sizeof(_wh_heap_entry_s)) + page_size;
			u64 new_count = new_size / sizeof(_wh_heap_entry_s);

			new_entries = wh_sys_memreq(new_size);

			wh_log_notice(("New memory for hashmap allocated! new size [ %u ] : old size [ %u ]"), new_size, _table.count * sizeof(_wh_heap_entry_s));

			wh_for (u64, i, _table.count) {
				i64 old_hash = 0;
				i64 new_hash = 0;

				if (nullptr == _table.entries[i].name) {
					new_entries[new_hash] = (_wh_heap_entry_s){ 0 };
					continue;
				}
				
				old_hash = wh_hash_simple(_table.entries[i].name, _table.count);
				new_hash = wh_hash_simple(_table.entries[i].name, new_count);

				if (nullptr != new_entries[new_hash].header) {
					wh_log_critical(("Collision detected for [ %9s ] and [ %9s ]!"), entry->name, name);
					goto go_realloc;
				}

				if (nullptr != _table.entries[old_hash].header) {
					new_entries[new_hash] = _table.entries[old_hash];
				}
			}

			if (nullptr != _table.entries) {
				wh_sys_memrel(_table.entries);
			}

			_table.entries = new_entries;
			_table.count = new_count;
		}

		hash = wh_hash_simple(name, _table.count);
		entry = &_table.entries[hash];

		if (nullptr != entry->name) {
			wh_log_critical(("Collision detected for [ %9s ] and [ %9s ]!"), entry->name, name);
			goto go_realloc;
		}

		entry->name = name;
		entry->header = header;
		++_table.used;
	}

	return header;
go_error_exit:
	return nullptr;
}

wh_heap_header_s* wh_heap_get(const char* name) {
	wh_heap_header_s* header = nullptr;
	_wh_heap_entry_s* entry = nullptr;
	i64 hash = 0;

	wh_spin_lock(&_table.lock) {
		hash = wh_hash_simple(name, _table.count);
		entry = &_table.entries[hash];

		if (nullptr == entry->header) {
			goto go_error_exit;
		}

		header = entry->header;
	}

go_error_exit:
	return header;
}

/*
 * The raw allocations functions
 *
 */
void* _wh_alloc_no_tracking(_wh_mem_alloc_params params) {
	void* mem = nullptr;
	params.bytes = (u64)wh_align((i64)params.bytes, 16);

	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

	switch (params.heap->stype) {
		case WH_STRUCT_TYPE_HEAP_ARENA:
			wh_spin_lock(&params.heap->locked) {
				mem = _wh_mem_alloc_arena(&params);
			}
			break;

		default:
		case WH_STRUCT_TYPE_HEAP_FREELIST:
			wh_spin_lock(&params.heap->locked) {
				mem = _wh_mem_alloc_freelist(&params);
			}
			break;
	}

	if (0 != params.flags) {
		if (WH_MEM_ZERO == params.flags) {
			memset(mem, 0, params.bytes);
		}
	}
	return mem;
}

void _wh_free_no_tracking(_wh_mem_free_params params) {
	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

	switch (params.heap->stype) {
		case WH_STRUCT_TYPE_HEAP_ARENA:
			wh_spin_lock(&params.heap->locked) {
				_wh_mem_free_arena(&params);
			}
			break;

		default:
		case WH_STRUCT_TYPE_HEAP_FREELIST:
			wh_spin_lock(&params.heap->locked) {
				_wh_mem_free_freelist(&params);
			}
		break;
	}
	
}

void* _wh_realloc_no_tracking(_wh_mem_realloc_params params) {
	void* mem = nullptr;

	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

	switch (params.heap->stype) {
		case WH_STRUCT_TYPE_HEAP_ARENA:
			wh_log_error(("Arena allocator don't support realloc"));
			break;

		default:
		case WH_STRUCT_TYPE_HEAP_FREELIST:
			wh_spin_lock(&params.heap->locked) {
				mem = _wh_mem_realloc_freelist(&params);
			}
		break;
	}

	return mem;
}

void* _wh_mem(_wh_mem_params params) {
	void* ptr = nullptr;

	if (0 == params.bytes) {
		if (nullptr != params.ptr) {
			if (WH_MEM_ZERO == params.flags) {
				memset(params.ptr, 0, params.bytes);
			}

			//atomic_fetch_sub(&_heap_main->ptr_count, 1);
			free(params.ptr);
		}

		goto go_exit;
	}

	if (nullptr == params.ptr) {
		ptr = malloc(params.bytes);
	} else {
		ptr = realloc(params.ptr, params.bytes);
	}

	if (nullptr == ptr) {
		goto go_failure_exit;
	}

	if (nullptr == params.ptr) {
		//atomic_fetch_add(&_heap_main->ptr_count, 1);
	}

	if (WH_MEM_ZERO == params.flags) {
		memset(ptr, 0, params.bytes);
	}

go_failure_exit:
go_exit:
	return ptr;
}

/*
 * The tracking functions for allocations
 *
 */
void* _wh_alloc_tracking(_wh_mem_alloc_params params) {
	void* out = _wh_alloc_no_tracking(params);

	if (nullptr == out) {
		goto go_error_exit;
	}

	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

	_wh_tracker_insert(params.owner, out, params.heap, params.line, params.file);
go_error_exit:
	return out;
}

void _wh_free_tracking(_wh_mem_free_params params) {
	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

	_wh_tracker_remove(params.owner, params.ptr);
	_wh_free_no_tracking(params);
}

void* _wh_realloc_tracking(_wh_mem_realloc_params params) {
	void* out = _wh_realloc_no_tracking(params);

	if (nullptr == out) {
		goto go_error_exit;
	}

	if (nullptr == params.heap) {
		params.heap = _heap_main;
	}

go_error_exit:
	return out;
}

/*
 * Debug functions
 *
 */
int32_t wh_mem_leak_count(void) {
	return 0;//atomic_load(&_heap_main->ptr_count);
}

void wh_heap_print_table() {
	wh_for (u64, i, _table.count) {
		wh_print(("Table entry [ index : %i ] [ name : %9s ] [ pointer : %u ]\n"), i, _table.entries[i].name ,_table.entries[i].header);
	}
}

void _wh_heap_print(_wh_heap_print_params params) {
	wh_heap_header_s* heap = params.heap;
	wh_heap_node_s* node = nullptr;

	if (nullptr == heap) {
		heap = _heap_main;
	}

	node = heap->freelist.nodes;
	wh_print(("\n"));

	while (nullptr != node) {
		if (node->flags & WH_MEM_IN_USE) {
			wh_print(("[\033[31mUSED \033[0m$k]"), node->bytes);
		} else {
			wh_print(("[\033[32mFREE \033[0m$k]"), node->bytes);
		}

		node = node->next;
	}
	
	wh_print(("\n\n"));
}

// TODO fix bug
i64 _wh_mem_scan(void) {
	i64 count = 0;
	_wh_heap_list_entry_s* current = _list.nodes;

	wh_spinlock(&_list.lock) {
		while (nullptr != current) {
			wh_log_debug(("Node found! [ %u ] next is [ %u ]"), current->ptr, current->next);

			wh_for(u64, i, current->owner_count) {
				if (nullptr == current->owners[i].owner) {
					continue;
				}

				if (*current->owners[i].owner != current->ptr) {
					wh_log_info(("Owner change! ptr [ %u ] != owner [ %u ] in file:line [ %s:%u ]"), current->owners[i].owner, current->ptr, current->owners[i].file, current->owners[i].line);
					
					current->owner_count--;
					current->owners[i].owner = current->owners[current->owner_count].owner;
					current->owners[i].line = current->owners[current->owner_count].line;
					current->owners[i].file = current->owners[current->owner_count].file;

					current->owners = realloc(current->owners, sizeof(_wh_heap_list_entry_s) * current->owner_count);
				}
			
			}

			if (0 == current->owner_count) {
				count++;
				wh_log_error(("LEAK FOUND! freeing..."));
				wh_free(current->heap, current->ptr, nullptr);
			}

			current = current->next;
		}
	}

	//usleep(100);
	return count;
}

/*
 * The main function for the memory system
 *
 */
wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params) {
	wh_heap_header_s* heap = nullptr;
	u64 old_bytes = params.bytes + sizeof(wh_heap_header_s);

	params.bytes = (u64)wh_align((i64)(params.bytes + sizeof(wh_heap_header_s)), getpagesize());

	_wh_alloc	= &_wh_alloc_tracking;
	_wh_realloc	= &_wh_realloc_tracking;
	_wh_free		= &_wh_free_tracking;

	wh_log_info(("requested [ $k ] giving [ $k ]"), old_bytes, params.bytes);

	if (nullptr != _heap_main) {
		if (nullptr == params.heap) {
			wh_log_debug(("Heap not set falling back to global"));
			params.heap = _heap_main;
		}

		heap = wh_alloc(params.heap, params.bytes, nullptr, WH_MEM_IS_HEAP, params.error);

		if (nullptr == heap) {
			wh_log_critical(("Failed to allocate system memory [ $n ]"), errno);
			goto go_error_exit;
		}
	} else {
		heap = wh_sys_memreq(params.bytes);

		if (nullptr == heap) {
			wh_log_critical(("Failed to allocate system memory [ $n ]"), errno);
			goto go_error_exit;
		}

		_heap_main = heap;
	}
	
	wh_heap_insert(params.name, heap);
	//wh_heap_print_table();

	wh_spin_lock(&heap->locked) {
		wh_heap_node_s* next = nullptr;
		heap->allocation_count = 0;

		if (WH_STRUCT_TYPE_UNKOWN == params.type) {
			params.type = WH_STRUCT_TYPE_HEAP_FREELIST;
		}

		heap->stype = params.type;

		switch (heap->stype) {
			case WH_STRUCT_TYPE_HEAP_ARENA:
				wh_log_debug(("Heap is type WH_STRUCT_TYPE_HEAP_ARENA"));

				heap->bytes_used = sizeof(wh_heap_header_s);
				heap->bytes_free = params.bytes - heap->bytes_used;
				heap->arena.start = wh_ptr_add(heap, sizeof(wh_heap_header_s));
				break;

			default:
			case WH_STRUCT_TYPE_HEAP_FREELIST:
				wh_log_debug(("Heap is type WH_STRUCT_TYPE_HEAP_FREELIST"));

				next = wh_ptr_add(heap, sizeof(wh_heap_header_s));
				memset(next, 0, sizeof(wh_heap_node_s));

				heap->bytes_used = sizeof(wh_heap_header_s) + sizeof(wh_heap_node_s);
				heap->bytes_free = params.bytes - heap->bytes_used;
				heap->freelist.nodes = next;

				// next node
				next->stype = WH_STRUCT_TYPE_HEAP_NODE;
				next->flags = 0;
				next->bytes = heap->bytes_free;
				next->data = wh_ptr_add(next, sizeof(wh_heap_node_s));
				break;
		}
		
	}

go_error_exit:
go_exit:
	return heap;
}

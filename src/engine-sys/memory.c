#include<stdlib.h>
#include<string.h>
#include<errno.h>


// my stuff
#include<wh-posix/stdatomic.h>
#include<wh-posix/unistd.h>
#include<wh-sys/atomic_lock.h>
#include<wh-sys/memory.h>
#include<wh-sys/memreq.h>
#include<wh/debug/logger.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>
#include<wh/memory/arena.h>
#include<wh/memory/freelist.h>

// hashmap
typedef struct {
	wh_heap_header_s* header;
	const char* name;
} _wh_heap_entry_s;

typedef struct {
	wh_atomic_lock_s lock;
	u64 count;
	u64 used;
	_wh_heap_entry_s* entries;
} _wh_heap_table_s;

static _wh_heap_table_s _table = { 0 };

// the global main heap
static wh_heap_header_s* _heap_main;

void* _wh_alloc_tracking(_wh_mem_alloc_params params);
void* _wh_realloc_tracking(_wh_mem_realloc_params params);

void _wh_free_tracking(_wh_mem_free_params params);
void _wh_disown_tracking(_wh_mem_free_params params);

extern void _wh_tracker_remove(void* owner, void* ptr);
extern void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file);

void* (*_wh_alloc)(_wh_mem_alloc_params params) = &_wh_alloc_tracking;
void* (*_wh_realloc)(_wh_mem_realloc_params params) = &_wh_realloc_tracking;

void  (*_wh_free)(_wh_mem_free_params params) = &_wh_free_tracking;
void (*_wh_disown)(_wh_mem_free_params params) = &_wh_disown_tracking;

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

	wh_spinlock_v2(&_table.lock) {
		if (_table.used >= _table.count) {
		go_realloc:
			wh_log_debug(("Expanding table"));
			_wh_heap_entry_s* new_entries = nullptr;

			if (3 <= retry++) {
				wh_log_critical(("Failed to realloc hashmap table!"));
				wh_lock_goto(&_table.lock, go_error_exit);
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

go_redo:
	hash = wh_hash_simple(name, _table.count);
	entry = &_table.entries[hash];

	if (nullptr == entry->header) {
		goto go_error_exit;
	}

	if (hash != wh_hash_simple(name, _table.count)) {
		goto go_redo;
	}

	header = entry->header;
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
			wh_spinlock_v2(&params.heap->locked) {
				mem = _wh_mem_alloc_arena(&params);
			}
			break;

		default:
		case WH_STRUCT_TYPE_HEAP_FREELIST:
			wh_spinlock_v2(&params.heap->locked) {
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
			wh_spinlock_v2(&params.heap->locked) {
				_wh_mem_free_arena(&params);
			}
			break;

		default:
		case WH_STRUCT_TYPE_HEAP_FREELIST:
			wh_spinlock_v2(&params.heap->locked) {
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
			wh_spinlock_v2(&params.heap->locked) {
				mem = _wh_mem_realloc_freelist(&params);
			}
		break;
	}

	return mem;
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

void _wh_disown_tracking(_wh_mem_free_params params) {
	if (nullptr == params.owner || nullptr == params.ptr) {
		wh_log_notice(("Cannot disown a nullptr"));
		return;
	}

	_wh_tracker_remove(params.owner, params.ptr);
}

WH_DEPRECATED("DON'T USE THIS FUNCTION!")
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
 * Debug functions
 *
 */
int32_t wh_mem_leak_count(void) {
	return 0;//atomic_load(&_heap_main->ptr_count);
}

void wh_heap_print_table(void) {
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

/*
 * The main function for the memory system
 *
 */
wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params) {
	wh_heap_header_s* heap = nullptr;
	u64 old_bytes = params.bytes + sizeof(wh_heap_header_s);

	params.bytes = (u64)wh_align((i64)(params.bytes + sizeof(wh_heap_header_s)), getpagesize());

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

	wh_spinlock_v2(&heap->locked) {
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
				heap->freelist.tail = next;

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

i8 _wh_heap_delete(void) {
	if (nullptr == _heap_main) {
		return -1;
	}

	wh_sys_memrel(_heap_main, _heap_main->bytes_free + _heap_main->bytes_used);

	return 0;
}

void _wh_memory_tracking(_wh_memory_tracking_params params) {
	if (0 == params.tracking_off) {
		_wh_alloc	= &_wh_alloc_tracking;
		_wh_realloc	= &_wh_realloc_tracking;
		_wh_free		= &_wh_free_tracking;
	} else {
		_wh_alloc	= &_wh_alloc_no_tracking;
		_wh_realloc	= &_wh_realloc_no_tracking;
		_wh_free		= &_wh_free_no_tracking;
	}
}

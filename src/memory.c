#include<stdlib.h>
#include<string.h>
#include<stdatomic.h>
#include<errno.h>

#include<stdio.h>

// my stuff
#include<wh/debug.h>
#include<wh/memory.h>
#include<wh/sys/memory.h>
#include<wh/maths/memory.h>
#include<wh/maths.h>

#include<wh/memory/arena.h>
#include<wh/memory/freelist.h>

#include<wh/wrap/unistd.h>

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

static wh_heap_header_s* _heap_main;

wh_heap_header_s* wh_heap_insert(const char* name, wh_heap_header_s* header) {
	u64 hash = 0;
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

			page_size += getpagesize();

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

			// TODO free memory
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
	u64 hash = 0;

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

void wh_heap_print_table() {
	wh_for (u64, i, _table.count) {
		wh_print(("Table entry [ index : %i ] [ name : %9s ] [ pointer : %u ]\n"), i, _table.entries[i].name ,_table.entries[i].header);
	}
}

wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params) {
	wh_heap_header_s* heap = nullptr;
	i64 old_bytes = params.bytes + sizeof(wh_heap_header_s);

	params.bytes = wh_align(params.bytes + sizeof(wh_heap_header_s), getpagesize());

	wh_log_info(("requested [ $k ] giving [ $k ]"), old_bytes, params.bytes);

	if (nullptr != _heap_main) {
		if (nullptr == params.heap) {
			wh_log_debug(("Heap not set falling back to global"));
			params.heap = _heap_main;
		}

		heap = wh_mem_alloc(params.heap, params.bytes, nullptr, WH_MEM_IS_HEAP, params.error);

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


void* _wh_mem_alloc(_wh_mem_alloc_params params) {
	void* mem = nullptr;
	params.bytes = wh_align(params.bytes, 16);

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

	return mem;
}

void _wh_mem_free(_wh_mem_free_params params) {
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

void* _wh_mem_realloc(_wh_mem_realloc_params params) {
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

void _wh_mem_insert(void* owner, void* ptr, wh_heap_header_s* heap) {
}

void _wh_mem_remove(void* owner, void* ptr) {
}

void _wh_mem_scan(void) {
}

void _wh_mem_init(void) {
}

void* _wh_mem(_wh_mem_params params) {
	void* ptr = NULL;

	if (0 == params.bytes) {
		if (NULL != params.ptr) {
			if (WH_MEM_ZERO == params.flags) {
				memset(params.ptr, 0, params.bytes);
			}

			//atomic_fetch_sub(&_heap_main->ptr_count, 1);
			free(params.ptr);
		}

		goto go_exit;
	}

	if (NULL == params.ptr) {
		ptr = malloc(params.bytes);
	} else {
		ptr = realloc(params.ptr, params.bytes);
	}

	if (NULL == ptr) {
		goto go_failure_exit;
	}

	if (NULL == params.ptr) {
		//atomic_fetch_add(&_heap_main->ptr_count, 1);
	}

	if (WH_MEM_ZERO == params.flags) {
		memset(ptr, 0, params.bytes);
	}

go_failure_exit:
go_exit:
	return ptr;
}

int32_t wh_mem_leak_count(void) {
	return 0;//atomic_load(&_heap_main->ptr_count);
}

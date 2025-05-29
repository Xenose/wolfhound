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

#include<wh/memory/arena.h>
#include<wh/memory/freelist.h>

#include<wh/wrap/unistd.h>

static wh_heap_header_s* _heap_main;

wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params) {
	wh_heap_header_s* heap = nullptr;
	i64 old_bytes = params.bytes + sizeof(wh_heap_header_s);

	params.bytes = wh_align(params.bytes + sizeof(wh_heap_header_s), getpagesize());

	wh_log_info(("requested [ %d ] giving [ %d ]"), old_bytes, params.bytes);

	if (nullptr != _heap_main) {
		if (nullptr == params.heap) {
			wh_log_debug(("Heap not set falling back to global"));
			params.heap = _heap_main;
		}

		heap = wh_mem_alloc(params.heap, params.bytes, nullptr, WH_MEM_IS_HEAP, params.error);
		printf("new address at [ %p ]\n", heap);

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

		wh_log_notice(("Setting main heap"));
		_heap_main = heap;
	}

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
			wh_print(("[\033[31mUSED \033[0m%iB] "), node->bytes);
		} else {
			wh_print(("[\033[32mFREE \033[0m%iB] "), node->bytes);
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

#include<wh-posix/errno.h>
#include<wh-posix/stdatomic.h>
#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/atomic_lock.h>
#include<wh-sys/memory.h>
#include<wh-sys/memreq.h>
#include<wh-sys/memory/tracker.h>
#include<wh-sys/data/hashmap.h>
#include<wh-sys/debug/logger.h>
#include<wh/maths/core.h>
#include<wh/maths/memory.h>

#include"_memory/dummy.c"
#include"_memory/freelist.c"
#include"_memory/arena.c"

// hashmap
typedef struct {
    wh_heap_header_s* header;
    const char* name;
} _wh_heap_entry_s;

static wh_hashmap_s _map = {
    .stype = WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS,
    .slots = nullptr,
    .type_size = sizeof(_wh_heap_entry_s),
    .resize_size = 4096,
};

void* _wh_disown_no_tracking(_wh_mem_free_params params) { return params.ptr; }
void* _wh_own_no_tracking(_wh_own_params params) { return params.ptr; }
// the global main heap
static wh_heap_header_s* _heap_main;

void* _wh_alloc_tracking(_wh_mem_alloc_params params);
void* _wh_realloc_tracking(_wh_mem_realloc_params params);

void _wh_free_tracking(_wh_mem_free_params params);
void* _wh_disown_tracking(_wh_mem_free_params params);
void* _wh_own_tracking(_wh_own_params params);

void* (*_wh_alloc)(_wh_mem_alloc_params params) = &_wh_alloc_tracking;
void* (*_wh_realloc)(_wh_mem_realloc_params params) = &_wh_realloc_tracking;

void  (*_wh_free)(_wh_mem_free_params params) = &_wh_free_tracking;

// ownership handling
void* (*_wh_disown)(_wh_mem_free_params params) = &_wh_disown_tracking;
void* (*_wh_own)(_wh_own_params params) = &_wh_own_tracking;


typedef struct {
    void* (*alloc)(_wh_mem_alloc_params* params);
    void* (*realloc)(_wh_mem_realloc_params* params);
    void (*free)(_wh_mem_free_params* params);
} _wh_alloc_funcs;

static _wh_alloc_funcs funcs[] = {
    { // arena
        .alloc =    &_wh_arena_alloc,
        .realloc =  &_wh_dummy_realloc,
        .free =     &_wh_arena_free,
    },
    { // bucket
        .alloc =    &_wh_dummy_alloc,
        .realloc =  &_wh_dummy_realloc,
        .free =     &_wh_dummy_free,
    },
    { // freelist
        .alloc =    &_wh_mem_alloc_freelist,
        .realloc =  &_wh_mem_realloc_freelist,
        .free =     &_wh_mem_free_freelist,
    }
};

/*
 * Hashmap functions
 *
 */
wh_heap_header_s* wh_heap_insert(const char* name, wh_heap_header_s* header) {
    wh_hashmap_insert(&_map, (void*)name, header);
    return header;
}

wh_heap_header_s* wh_heap_get(const char* name) {
    wh_heap_header_s* header = wh_hashmap_get(&_map, (void*)name);
    return header;
}


/*
 * The raw allocations functions
 *
 */
void* _wh_alloc_no_tracking(_wh_mem_alloc_params params) {
    i64 index = 0;
    void* mem = nullptr;

    if (nullptr == params.heap) {
        params.heap = _heap_main;
    }

    params.bytes = (u64)wh_align((i64)params.bytes, 16);
    index = params.heap->stype - WH_STRUCT_TYPE_HEAP_ARENA;

    wh_spinlock_v3(&params.heap->locked) {
        mem = funcs[index].alloc(&params);
    }

    if (0 != params.flags) {
        if (WH_MEM_ZERO == params.flags) {
            memset(mem, 0, params.bytes);
        }
    }

    return mem;
}

void* _wh_realloc_no_tracking(_wh_mem_realloc_params params) {
    i64 index = 0;
    void* mem = nullptr;

    if (nullptr == params.heap) {
        params.heap = _heap_main;
    }

    index = params.heap->stype - WH_STRUCT_TYPE_HEAP_ARENA;

    wh_spinlock_v3(&params.heap->locked) {
        mem = funcs[index].realloc(&params);
    }

    return mem;
}

void _wh_free_no_tracking(_wh_mem_free_params params) {
    i64 index = 0;

    if (nullptr == params.heap) {
        params.heap = _heap_main;
    }

    if (nullptr == params.ptr) {
        wh_log_error(("trying to free nullptr"));
    }

    index = params.heap->stype - WH_STRUCT_TYPE_HEAP_ARENA;

    wh_spinlock_v3(&params.heap->locked) {
        funcs[index].free(&params);
    }
}

void* _wh_calloc(_wh_calloc_params params) {
    void* mem = nullptr;
    u64 bytes = params.count * params.bytes;

    _wh_mem_alloc_params p = {
        .heap   = params.heap,
        .bytes  = bytes,
        .owner  = params.owner,
        .flags  = params.flags,
        .line   = params.line,
        .file   = params.file,
    };

    mem = _wh_alloc(p);

    if (nullptr != mem) {
        memset(mem, 0, bytes);
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

void* _wh_disown_tracking(_wh_mem_free_params params) {
    if (nullptr == params.owner || nullptr == params.ptr) {
        wh_log_notice(("Cannot disown a nullptr"));
        return params.ptr;
    }

    _wh_tracker_remove(params.owner, params.ptr);
    return params.ptr;
}

void* _wh_own_tracking(_wh_own_params params) {
    if (nullptr == params.owner || nullptr == params.ptr) {
        wh_log_notice(("Cannot own a nullptr"));
        return params.ptr;
    }

    _wh_tracker_add(params.owner, params.ptr, nullptr, params.line, params.file);
    return params.ptr;
}


/*
 * Debug functions
 * needs to add a global counter after removing the old code.
 */
int32_t wh_mem_leak_count(void) {
    return 0;//atomic_load(&_heap_main->ptr_count);
}

void _wh_heap_print_table_for_each(void* data) {
    _wh_heap_entry_s* i = data;
    wh_print(("Table entry [ name : %9s ] [ pointer : %u ]\n"), i->name, i->header);
}

void wh_heap_print_table(void) {
    _wh_hashmap_foreach(&_map, &_wh_heap_print_table_for_each);
}

void _wh_heap_print(_wh_heap_print_params params) {
    wh_heap_header_s* heap = params.heap;
    wh_heap_node_s* node = nullptr;

    if (nullptr == heap) {
        heap = _heap_main;
    }

    node = heap->freelist.head;
    wh_print(("\n"));

    while (nullptr != node) {
        if (node->flags & WH_MEM_IN_USE) {
            wh_print(("[\033[31mUSED \033[0m$k ] "), node->bytes);
        } else {
            wh_print(("[\033[32mFREE \033[0m$k ] "), node->bytes);
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

    params.bytes = (u64)wh_align((i64)(params.bytes + sizeof(wh_heap_header_s)), sysconf(_SC_PAGESIZE));

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
        heap->bytes_total = params.bytes;
    }

    wh_heap_insert(params.name, heap);

    wh_spinlock_v3(&heap->locked) {
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
                // heap->bytes_free = params.bytes - heap->bytes_used;
                heap->arena.start = wh_ptr_add(heap, sizeof(wh_heap_header_s));
                break;

            default:
            case WH_STRUCT_TYPE_HEAP_FREELIST:
                wh_log_debug(("Heap is type WH_STRUCT_TYPE_HEAP_FREELIST"));

                next = wh_ptr_add(heap, sizeof(wh_heap_header_s));
                memset(next, 0, sizeof(wh_heap_node_s));

                heap->bytes_used = sizeof(wh_heap_header_s) + sizeof(wh_heap_node_s);
                // heap->bytes_free = params.bytes - heap->bytes_used;
                heap->freelist.head = next;
                heap->freelist.tail = next;

                // next node
                next->stype = WH_STRUCT_TYPE_HEAP_NODE;
                next->flags = 0;
                
                next->bytes = (u64)heap->bytes_total - (u64)heap->bytes_used;
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

    wh_sys_memrel(_heap_main, (u64)_heap_main->bytes_total);

    return 0;
}

void _wh_memory_tracking(_wh_memory_tracking_params params) {
    if (0 == params.tracking_off) {
        _wh_alloc       = &_wh_alloc_no_tracking;
        _wh_realloc     = &_wh_realloc_no_tracking;
        _wh_free        = &_wh_free_no_tracking;

        _wh_disown      = &_wh_disown_no_tracking;
    } else {
        _wh_alloc       = &_wh_alloc_tracking;
        _wh_realloc     = &_wh_realloc_tracking;
        _wh_free        = &_wh_free_tracking;

        _wh_disown      = &_wh_disown_tracking;
    }
}

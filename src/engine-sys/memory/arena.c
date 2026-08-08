#include<wh/debug/logger.h>
#include<wh/memory/arena.h>

void* _wh_mem_alloc_arena(_wh_mem_alloc_params* params)  {
    void* out = nullptr;
    void* ptr = params->heap->arena.start;

    if (params->heap->bytes_free <= params->bytes) {
        goto go_error_exit;
    }

    out = wh_ptr_add(
            params->heap->arena.start, params->heap->bytes_used);

    params->heap->bytes_free -= params->bytes;
    params->heap->bytes_used += params->bytes;

    wh_log_info(("Allocating arena memory [ %d ] memory left [ %d ]"),
            params->bytes, params->heap->bytes_free);
go_error_exit:
    return out;
}

void _wh_mem_free_arena(_wh_mem_free_params* params) {
    wh_heap_header_s* heap = params->heap;

    heap->bytes_free += (heap->bytes_used - sizeof(wh_heap_header_s));
    heap->bytes_used = sizeof(wh_heap_header_s);
}

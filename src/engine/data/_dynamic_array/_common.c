#ifndef _wh_source_guard_data_common_darray_
#define _wh_source_guard_data_common_darray_

#include<wh/data/dynamic_array.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-sys/memory.h>
#include<wh/debug/logger.h>

void _wh_darray_init_common(_wh_darray_init_params* params, void* mem) {
    wh_log_info(("Creating array size of %i and type size of %i"), params->count, params->type_size);

    if (nullptr == params->array->memory) {
        wh_log_error(("Failed to allocate array"));
    }

    *params->array = (wh_darray_s) {
        .stype      = 0,
        .lock       = { 0 },
        .memory     = mem,
        
        .type_size  = params->type_size,
        .node_count = params->count,
        .heap       = params->heap,
    };

    wh_log_debug(("Memory: %u, Count: %u, Type-Size: %u"),
            params->array->memory, params->array->node_count, params->array->type_size);
}

#endif /* _wh_source_guard_data_common_darray_ */

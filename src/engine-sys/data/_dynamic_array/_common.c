#ifndef _wh_source_guard_data_common_darray_
#define _wh_source_guard_data_common_darray_

#include<wh-sys/data/dynamic_array.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-sys/memory.h>
#include<wh-sys/debug/logger.h>

void _wh_darray_init_common(_wh_darray_init_params* params, void* mem) {
    wh_log_info(("Creating array size of %i and type size of %i"), params->count, params->type_size);

    if (nullptr == mem) {
        wh_log_error(("Failed to allocate array [ ptr : %p ]"), mem);
        return;
    }

    *params->array = (wh_darray_s) {
        .stype      = params->stype,
        .lock       = { 0 },
        .memory     = mem,
        
        .type_size  = params->type_size,
        .node_count = params->count,
        .heap       = params->heap,
    };

    wh_log_debug(("Memory: %p, Count: %u, Type-Size: %u"),
            params->array->memory, params->array->node_count, params->array->type_size);
}

void* _wh_darray_get_common(_wh_darray_get_params* params) {
    void* data = nullptr;

    if (params->array->node_count < params->index) {
        wh_log_error(("Array outside range!"));
        return data;
    }

    // Calculating the data offset
    data = wh_ptr_offset(params->array->memory, params->array->type_size * params->index);
    return data;
}

void* _wh_darray_set_common(_wh_darray_set_params* params) {
    void* data = nullptr;

    if (params->array->node_count < params->index) {
        wh_log_error(("Array outside range!"));
        return nullptr;
    }
    
    data = wh_ptr_offset(params->array->memory, params->array->type_size * params->index);
    memcpy(data, params->value, params->array->type_size);

    return data;
}

i8 _wh_darray_resize_common(_wh_darray_resize_params* params, void* data, u64 count) {
    if (nullptr == data) {
        wh_log_error(("Failed to expand array!"));
        goto go_error_exit;
    }

    memcpy(data, params->array->memory, params->array->type_size * count > params->array->node_count ? // preventing overflow risk
        params->array->node_count : count);

    
    params->array->node_count = count;
    return 0;
go_error_exit:
    return -1;
}

void _wh_darray_for_each_common(_wh_darray_for_each_params* params) {
    for (u64 i = 0; i < params->array->node_count; i++) {
        params->loop(i, wh_ptr_offset(params->array->memory, params->array->type_size * i));
    }
}

#endif /* _wh_source_guard_data_common_darray_ */

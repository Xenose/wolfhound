#include<wh/data/dynamic_array.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>

#include<wh/debug/logger.h>

void _wh_darray_init_std(_wh_darray_init_params* params) {
    wh_log_info(("Creating array size of %i and type size of %i"), params->count, params->type_size);

    params->array->memory = calloc(params->count, params->type_size);

    if (nullptr == params->array->memory) {
        wh_log_error(("Failed to allocate array"));
    }
    
    params->array->node_count = params->count;
    params->array->type_size = params->type_size;

    wh_log_debug(("Memory: %u, Count: %u, Type-Size: %u"),
            params->array->memory, params->array->node_count, params->array->type_size);
}

void* _wh_darray_get_std(_wh_darray_get_params* params) {
    void* data = nullptr;

    if (params->array->node_count < params->index) {
        wh_log_error(("Array outside range!"));
        return data;
    }

    // Calculating the data offset
    data = wh_ptr_offset(params->array->memory, params->array->type_size * params->index);
    return data;
}

void* _wh_darray_set_std(_wh_darray_set_params* params) {
    void* data = nullptr;

    if (params->array->node_count < params->index) {
        wh_log_error(("Array outside range!"));
        return nullptr;
    }
    
    data = wh_ptr_offset(params->array->memory, params->array->type_size * params->index);
    wh_log_debug(("Offset is %u"), data);
    memcpy(data, params->value, params->array->type_size);

    return data;
}

i8 _wh_darray_resize_std(_wh_darray_resize_params* params) {
    void* data = nullptr;
    u64 count = (u64)(((i64)params->array->node_count) + params->count); // Allow resizing using negative numbers

    data = calloc(count, params->array->type_size);

    if (nullptr == data) {
        wh_log_error(("Failed to expand array!"));
        goto go_error_exit;
    }

    wh_log_debug(("Array resized from [ %u ] to [ %u ]"), params->array->node_count, count);

    memcpy(
            data, 
            params->array->memory, 
            params->array->type_size * count > params->array->node_count ? // preventing overflow risk
                params->array->node_count : 
                count
    );

    free(params->array->memory);
    params->array->memory = data;
    params->array->node_count = count;

    return 0;
go_error_exit:
    return -1;
}

void _wh_darray_delete_std(_wh_darray_delete_param params) {
}

void _wh_darray_for_each_std(_wh_darray_for_each_params* params) {
    for (u64 i = 0; i < params->array->node_count; i++) {
        params->loop(i, wh_ptr_offset(params->array->memory, params->array->type_size * i));
    }
}

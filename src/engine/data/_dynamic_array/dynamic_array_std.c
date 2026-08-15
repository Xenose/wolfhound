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

void _wh_darray_push_back_std(_wh_darray_push_back_params params) {
}

void _wh_darray_delete_std(_wh_darray_delete_param params) {
}

void _wh_darray_for_each_std(_wh_darray_for_each_params params) {
}

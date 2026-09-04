#include<wh-sys/data/dynamic_array.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>

#include<wh-sys/debug/logger.h>

#include"_common.c"

void _wh_darray_init_std(_wh_darray_init_params* params) {
    wh_log_info(("Creating array size of %i and type size of %i"), params->count, params->type_size);

    void* mem = calloc(params->count, params->type_size);
    _wh_darray_init_common(params, mem);
}

void* _wh_darray_get_std(_wh_darray_get_params* params) {
    return _wh_darray_get_common(params);
}

void* _wh_darray_set_std(_wh_darray_set_params* params) {
    return _wh_darray_set_common(params);
}

i8 _wh_darray_resize_std(_wh_darray_resize_params* params) {
    void* data = nullptr;
    u64 count = (u64)(((i64)params->array->node_count) + params->count); // Allow resizing using negative numbers
    
    data = calloc(count, params->array->type_size);
    
    if (-1 == _wh_darray_resize_common(params, data, count)) {
        goto go_error_exit;
    }

    free(params->array->memory);
    params->array->memory = data;

    return 0;
go_error_exit:
    return -1;
}

void _wh_darray_delete_std(_wh_darray_delete_param params) {
}

void _wh_darray_for_each_std(_wh_darray_for_each_params* params) {
    _wh_darray_for_each_common(params);
}

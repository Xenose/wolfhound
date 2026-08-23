#include<wh/data/dynamic_array.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-sys/memory.h>
#include<wh/debug/logger.h>

#include"_common.c"

void _wh_darray_init_wolf(_wh_darray_init_params* params) {
    void* mem = wh_calloc(params->heap, params->count, params->type_size);
    _wh_darray_init_common(params, mem);
}

void* _wh_darray_get_wolf(_wh_darray_get_params* params) {
    void* data = nullptr;

    if (params->array->node_count < params->index) {
        return data;
    }

    data = wh_ptr_offset(params->array->memory, params->array->type_size * params->index);
    return data;
}

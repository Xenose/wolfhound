#include<wh-sys/data/dynamic_array.h>

#include"_dynamic_array/dynamic_array_wolf.c"
#include"_dynamic_array/dynamic_array_std.c"

typedef struct {
    void (*init)(_wh_darray_init_params* params);
    void* (*get)(_wh_darray_get_params* params);
    void* (*set)(_wh_darray_set_params* params);
    i8 (*resize)(_wh_darray_resize_params* params);
    void (*delete)(_wh_darray_delete_param params);
    void (*for_each)(_wh_darray_for_each_params* params);
} _map_func;

static _map_func _funcs[] = {
    {
        .init       = _wh_darray_init_wolf,
        .get        = _wh_darray_get_wolf,
        .set        = _wh_darray_set_wolf,
        .resize     = _wh_darray_resize_wolf,
        .for_each   = _wh_darray_for_each_wolf,
    },
    {
    },
    {
        .init       = _wh_darray_init_std,
        .get        = _wh_darray_get_std,
        .set        = _wh_darray_set_std,
        .resize     = _wh_darray_resize_std,
        .for_each   = _wh_darray_for_each_std,
    },
};

void _wh_darray_init(_wh_darray_init_params params) {
    u64 fi = 0; // function index

    params.array->stype = params.stype;
    fi = ((u64)params.stype) - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF;
    _funcs[fi].init(&params);
}

void* _wh_darry_get(_wh_darray_get_params params) {
    u64 fi = 0; // function index
    
    fi = ((u64)params.array->stype) - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF;
    return _funcs[fi].get(&params);
}

void* _wh_darray_set(_wh_darray_set_params params) {
    u64 fi = 0; // function index

    fi = ((u64)params.array->stype) - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF;
    return _funcs[fi].set(&params);
}

i8 _wh_darray_resize(_wh_darray_resize_params params) {
    u64 fi = 0; // function index

    fi = ((u64)params.array->stype) - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF;
    
    if (-1 == _funcs[fi].resize(&params)) {
        goto go_error_exit;
    }

    return 0;
go_error_exit:
    return -1;
}

void _wh_darray_delete(_wh_darray_delete_param params) {
}

void _wh_darray_for_each(_wh_darray_for_each_params params) {
    u64 fi = 0; // function index

    fi = ((u64)params.array->stype) - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF;
    _funcs[fi].for_each(&params);
}

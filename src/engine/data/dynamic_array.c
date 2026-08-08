#include<wh/data/dynamic_array.h>

#include"_dynamic_array/dynamic_array_std.c"

typedef struct {
    void (*init)(_wh_darray_init_params* params);
} _map_func;

static _map_func _funcs[] = {
    {},
    {},
    {
        .init = _wh_darray_init_std,
    },
};

void _wh_darray_init(_wh_darray_init_params params) {
    u64 fi = 0; // function index

    fi = ((u64)params.stype) - WH_STRUCT_TYPE_LLIST_SINGLE;

    _funcs[fi].init(&params);
}

void _wh_darray_insert(_wh_darray_insert_params params) {
}

void _wh_darray_push_back(_wh_darray_push_back_params params) {
}

void _wh_darray_delete(_wh_darray_delete_param params) {
}

void _wh_darray_for_each(_wh_darray_for_each_params params) {
}

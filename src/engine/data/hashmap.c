#include<wh/data/hashmap.h>

#include"_hashmap/lazy_simple_sys.c"

typedef struct {
    void* (*reallocate)(wh_hashmap_s* map);
    i8 (*delete)(wh_hashmap_s* map, void* value);
    i8 (*insert)(_wh_hashmap_insert_params* params);
    void* (*get)(wh_hashmap_s* map, void* key);
    i8 (*foreach)(wh_hashmap_s* map, void (*func)(void* value));
} _map_func;

static _map_func _funcs[] = {
    {},
    {
        .reallocate     = _reallocate_lazy_simple_sys,
        .delete         = _delete_lazy_simple_sys,
        .insert         = _insert_lazy_simple_sys,
        .get            = _get_lazy_simple_sys,
        .foreach        = _wh_lazy_simple_foreach,
    }, // extern str ptr
    {},

    {},
    {},
    {},

    {},
    {},
    {},

    {},
    {
        .reallocate     = _reallocate_lazy_simple_sys,
        .delete	        = _delete_lazy_simple_sys,
        .insert         = _insert_lazy_simple_sys,
        .get            = _get_lazy_simple_sys,
        .foreach        = _wh_lazy_simple_foreach,
    }, // ptr lazy
    {},
};

void* _wh_hashmap_search(wh_hashmap_s* map, void* value) {
    i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
    return nullptr;
}

i8 _wh_hashmap_insert(_wh_hashmap_insert_params params) {
    i64 func_index = params.map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
    return _funcs[func_index].insert(&params);
}

void* _wh_hashmap_get(_wh_hashmap_get_params params) {
    i64 func_index = params.map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
    return _funcs[func_index].get(params.map, (void*)params.key);
}

i8 _wh_hashmap_delete(_wh_hashmap_delete_params params) {
    i64 func_index = params.map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
    return _funcs[func_index].delete(params.map, (void*)params.key);
}

i8 _wh_hashmap_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
    i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
    return _funcs[func_index].foreach(map, func);
}

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
    wh_hashmap_s out = { 0 };

    out.stype = params.stype;
    out.type_size = params.type_size;
    out.slot_count = params.init_size;

    return out;
}

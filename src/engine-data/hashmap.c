#include<wh-data/hashmap.h>

#include"_hashmap/lazy_simple_sys.c"

static void* (*_reallocate[])(wh_hashmap_s* map) = {
	nullptr,
	_reallocate_lazy_simple_sys,
};


static i8 (*_delete[])(wh_hashmap_s* map, void* value) = {
	nullptr,
	_delete_lazy_simple_sys,
};

static i8 (*_insert[])(_wh_hashmap_insert_params* params) = {
	nullptr,
	_insert_lazy_simple_sys,
};

static void* (*_get[])(wh_hashmap_s* map, void* key) = {
	nullptr,
	_get_lazy_simple_sys,
};

static i8 (*_foreach[])(wh_hashmap_s* map, void (*func)(void* value)) = {
	nullptr,
	_wh_lazy_simple_foreach,
};

void* _wh_hashmap_search(wh_hashmap_s* map, void* value) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return nullptr;
}

i8 _wh_hashmap_insert(_wh_hashmap_insert_params params) {
	i64 func_index = params.map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return _insert[func_index](&params);
}

void* _wh_hashmap_get(_wh_hashmap_get_params params) {
	i64 func_index = params.map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return _get[func_index](params.map, (void*)params.key);
}

void* _wh_hashmap_delete(wh_hashmap_s* map, void* key) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return nullptr;
}

i8 _wh_hashmap_foreach(wh_hashmap_s* map, void (*func)(void* value)) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	wh_print(("hello!\n"));
	return _foreach[func_index](map, func);
}

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
	wh_hashmap_s out = { 0 };

	out.stype = params.stype;
	out.type_size = params.type_size;
	out.slot_count = params.init_size;

	return out;
}

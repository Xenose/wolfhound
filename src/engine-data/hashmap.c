#include<wh-data/hashmap.h>

#include"_hashmap/lazy_simple_sys.c"

static void* (*_reallocate[])(wh_hashmap_s* map) = {
	nullptr,
	_reallocate_lazy_simple_sys,
};


static i8 (*_delete[])(wh_hashmap_s* map, void* value) = {
	nullptr,
	nullptr,
};

static i8 (*_insert[])(wh_hashmap_s* map, void* key, void* value) = {
	nullptr,
	_insert_lazy_simple_sys,
};

static void* (*_get[])(wh_hashmap_s* map, void* key) = {
	nullptr,
	nullptr,
};

void* _wh_hashmap_search(wh_hashmap_s* map, void* value) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return nullptr;
}

i8 _wh_hashmap_insert(wh_hashmap_s* map, void* key, void* value) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return _insert[func_index](map, key, value);
}

void* _wh_hashmap_get(wh_hashmap_s* map, void* key) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return _get[func_index](map, key);
}

void* _wh_hashmap_delete(wh_hashmap_s* map, void* key) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return nullptr;
}

void* _wh_hashmap_foreach(wh_hashmap_s* map) {
	i64 func_index = map->stype - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF;
	return nullptr;
}

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
	wh_hashmap_s out = { 0 };

	out.stype = params.stype;
	out.type_size = params.type_size;
	out.slot_count = params.init_size;

	return out;
}

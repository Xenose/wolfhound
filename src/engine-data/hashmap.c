#include<wh-data/hashmap.h>

#include"_hashmap/lazy_simple_sys.c"

static void* (*_reallocate[])(wh_hashmap_s* map) = {
	_reallocate_lazy_simple_sys,
};

static i8 (*_insert[])(wh_hashmap_s* map, void* value) = {
	_insert_lazy_simple_sys,
};

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
	wh_hashmap_s out = { 0 };

	out.stype = params.stype;
	out.type_size = params.type_size;
	out.slot_count = params.init_size;

	return out;
}

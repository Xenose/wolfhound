#include<wh-data/hashmap.h>

static void* (*_allocate[])(wh_hashmap_s* map) = {
	nullptr
};

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
	wh_hashmap_s out = { 0 };

	out.stype = params.stype;
	out.type_size = params.type_size;
	out.slot_count = params.init_size;

	return out;
}

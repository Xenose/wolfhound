#include<wh-data/hashmap.h>

wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params) {
	wh_hashmap_s out = { 0 };

	out.stype = params.stype;
	return out;
}

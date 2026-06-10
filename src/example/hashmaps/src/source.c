#include<wh-data/hashmap.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

void hash_foreach(void* value) {
	wh_log_debug(("--> %i"), *((int*)value));
}

int main(int arc, char* const* arv) {
	wh_hashmap_s l = wh_hashmap_init_mmap_lazy(sizeof(int));

	wh_signalar_init(arv[0]);

	// TODO fix items with the same id
	wh_hashmap_insert(&l, "test", WH_INT(10));
	wh_hashmap_insert(&l, "test", WH_INT(10));
	wh_hashmap_insert(&l, "test2", WH_INT(15));
	wh_hashmap_insert(&l, "test3", WH_INT(30));
	wh_hashmap_insert(&l, "test4", WH_INT(35));
	wh_hashmap_insert(&l, "test5", WH_INT(15));
	wh_hashmap_insert(&l, "test6", WH_INT(30));
	wh_hashmap_insert(&l, "test7", WH_INT(35));
	wh_hashmap_insert(&l, "test8", WH_INT(35));
	wh_hashmap_insert(&l, "test9", WH_INT(35));
	wh_hashmap_insert(&l, "test10", WH_INT(35));
	wh_hashmap_insert(&l, "test11", WH_INT(35));
	wh_hashmap_insert(&l, "test12", WH_INT(35));
	wh_hashmap_insert(&l, "test13", WH_INT(35));
	wh_hashmap_insert(&l, "test14", WH_INT(35));
	wh_hashmap_insert(&l, "test15", WH_INT(35));
	wh_hashmap_insert(&l, "test16", WH_INT(35));
	wh_hashmap_insert(&l, "test17", WH_INT(35));
	wh_hashmap_insert(&l, "test18", WH_INT(35));
	wh_hashmap_insert(&l, "test19", WH_INT(35));
	wh_hashmap_insert(&l, "test20", WH_INT(35));

	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test2"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test3"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test4"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test5"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test6"));
	wh_log_debug(("%i\n"), *(int*)wh_hashmap_get(&l, "test7"));


	_wh_hashmap_foreach(&l, &hash_foreach);
	return 0;
}

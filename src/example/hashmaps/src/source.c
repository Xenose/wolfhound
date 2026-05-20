#include<wh-data/hashmap.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

int main(int arc, char* const* arv) {
	wh_hashmap_s l = wh_hashmap_init_mmap_lazy(sizeof(int));

	wh_signalar_init(arv[0]);

	// TODO fix items with the same id
	wh_hashmap_insert(&l, "test", WH_INT(10));
	wh_hashmap_insert(&l, "test2", WH_INT(15));

	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test"));
	wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test2"));
	return 0;
}

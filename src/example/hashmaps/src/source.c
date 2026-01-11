#include<wh-data/hashmap.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

int main(int arc, char* const* arv) {
	wh_hashmap_s l = wh_hashmap_init_mmap_lazy(sizeof(int));

	wh_signalar_init(arv[0]);

	return 0;
}

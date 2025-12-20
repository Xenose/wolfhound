#include<wh-sys/list.h>

int main(int arc, char* const* arv) {
	wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

	wh_sys_list_insert(&l, 0, (int[]){ 20 });

	return 0;
}

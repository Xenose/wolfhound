#include<stdio.h>
#include<wh-sys/list.h>

int main(int arc, char* const* arv) {
	wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

	wh_sys_list_insert(&l, 0, (int[]){ 20 });
	wh_sys_list_insert(&l, 0, (int[]){ 40 });

	printf("--> %i\n", *wh_s2_list_get(int, &l, 0));

	return 0;
}

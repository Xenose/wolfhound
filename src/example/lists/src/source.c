#include<stdio.h>
#include<wh/debug/signalar.h>
#include<wh-sys/list.h>

int main(int arc, char* const* arv) {
	wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

	wh_signalar_init(arv[0]);

	wh_sys_list_insert(&l, 0, (int[]){ 20 });
	printf("--> %i\n", *wh_s2_list_get(int, &l, 0));
	
	wh_sys_list_insert(&l, 1, (int[]){ 40 });
	printf("--> %i\n", *wh_s2_list_get(int, &l, 0));
	
	wh_sys_list_insert(&l, 1, (int[]){ 50 });
	wh_sys_list_insert(&l, 3, (int[]){ 150 });
	printf("--> %i\n", *wh_s2_list_get(int, &l, 0));

	wh_sys_list_insert(&l, 2, (int[]){ 10 });
	wh_sys_list_insert(&l, 0, (int[]){ 5 });

	printf("Test\n");

	printf("--> %i\n", *wh_s2_list_get(int, &l, 0));
	printf("--> %i\n", *wh_s2_list_get(int, &l, 1));
	printf("--> %i\n", *wh_s2_list_get(int, &l, 2));
	printf("--> %i\n", *wh_s2_list_get(int, &l, 3));

	return 0;
}

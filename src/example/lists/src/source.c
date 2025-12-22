#include<stdio.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

int main(int arc, char* const* arv) {
	wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

	wh_signalar_init(arv[0]);

	wh_sys_list_insert(&l, 0, (int[]){ 20 });
	wh_sys_list_insert(&l, 0, (int[]){ 20 });
	wh_sys_list_insert(&l, 0, (int[]){ 5 });
	wh_sys_list_insert(&l, 3, (int[]){ 40 });
	wh_sys_list_insert(&l, 1, (int[]){ 40 });
	wh_sys_list_insert(&l, 1, (int[]){ 50 });
	wh_sys_list_insert(&l, 3, (int[]){ 150 });
	wh_sys_list_insert(&l, 2, (int[]){ 10 });

	if (nullptr != wh_list_search(&l, (int[]){ 20 })) {
		wh_log_debug(("Item found!"));
	}

	for (int i = 0; i < l.node_count; i++) {
		printf("--> %i\n", *wh_s2_list_get(int, &l, i));
	}

	return 0;
}

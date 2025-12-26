#include<stdio.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>

int main(int arc, char* const* arv) {
	wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

	wh_signalar_init(arv[0]);

	wh_list_insert(&l, 0, WH_INT(20));
	wh_list_insert(&l, 0, WH_INT(20));
	wh_list_insert(&l, 0, WH_INT(5));
	wh_list_insert(&l, 3, WH_INT(40));
	wh_list_insert(&l, 1, WH_INT(40));
	wh_list_insert(&l, 1, WH_INT(50));
	wh_list_insert(&l, 3, WH_INT(150));
	wh_list_insert(&l, 2, WH_INT(10));

	wh_list_delete(&l, 3);

	wh_for(int, i, 10) {
		wh_list_push_back(&l, &i);
	}

	if (nullptr != wh_list_search(&l, WH_INT(20))) {
		wh_log_debug(("Item found!"));
	}

	for (int i = 0; i < l.node_count; i++) {
		printf("--> %i\n", *wh_list_get(int, &l, i));
	}

	return 0;
}

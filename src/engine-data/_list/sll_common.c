#ifndef _wh_c_sll_common_
#define _wh_c_sll_common_

#include<wh/data/list.h>
#include<wh-data/list.h>

static void* _wh_data_sll(void* node) {
	wh_sllist_item_s* n = node;
	return n->data;
}

static void _wh_insert_sll(_wh_sys_list_insert* params, void* current, void* previous, void* node) {
	wh_sllist_item_s* c = current;
	wh_sllist_item_s* p = previous;
	wh_sllist_item_s* n = node;

	if (nullptr != p) {
		p->p_next = node;
	}
	n->p_next = c;
}

static i8 _wh_get_index_sll(wh_list_s* list, u64 index, void** current, void** previous) {
	wh_sllist_item_s* p = nullptr;
	wh_sllist_item_s* c = list->head;

	if (index > list->node_count) {
		goto go_error_exit;
	}

	while (0 < index--) {
		p = c;
		c = c->p_next;
	}

	*current = c;
	*previous = p;
	return 0;

go_error_exit:
	*current = nullptr;
	*previous = nullptr;
	return -1;
}

static void* _wh_list_search_sll(_wh_list_search_params* params) {
}

#endif

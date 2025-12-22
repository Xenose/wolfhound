#ifndef _wh_c_sll_common_
#define _wh_c_sll_common_

#include<wh/data/list.h>
#include<wh-data/list.h>


static void _wh_insert_sll(_wh_sys_list_insert* params, void* current, void* previous, void* node) {
	wh_sllist_item_s* c = current;
	wh_sllist_item_s* p = previous;
	wh_sllist_item_s* n = node;

	if (nullptr != p) {
		p->p_next = node;
	}
	n->p_next = c;
}

#endif

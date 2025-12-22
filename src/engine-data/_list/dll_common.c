#ifndef _wh_c_dll_common_
#define _wh_c_dll_common_

#include<wh/data/list.h>
#include<wh-data/list.h>

static void _wh_insert_dll(_wh_sys_list_insert* params, void* current, void* previous, void* node) {
	wh_dllist_item_s* c = current;
	wh_dllist_item_s* p = previous;
	wh_dllist_item_s* n = node;

	n->p_next = c;
	n->p_previous = p;

	if (nullptr != c) {
		c->p_previous = node;

		if (nullptr == c->p_next) {
			params->list->tail = c;
		}
	} else {
		p = params->list->tail;
		params->list->tail = node;
	}

	if (nullptr != p) {
		p->p_next = node;
	} else {
		params->list->head = node;
	}
}

#endif

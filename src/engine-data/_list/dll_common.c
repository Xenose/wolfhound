#ifndef _wh_c_dll_common_
#define _wh_c_dll_common_

#include<string.h>
#include<wh/data/list.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>

static void* _wh_data_dll(void* node) {
	wh_dllist_item_s* n = node;
	return n->data;
}

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

static void _wh_push_back_dll(_wh_list_push_back_params* params, void* node) {
	wh_dllist_item_s* n = node;

	if (nullptr == params->list->head) {
		params->list->head = n;
	}

	if (nullptr != params->list->tail) {
		((wh_dllist_item_s*)params->list->tail)->p_next = n;
	}

	n->p_previous = params->list->tail;
	params->list->tail = n;
}

static i8 _wh_get_index_dll(wh_list_s* list, u64 index, void** current, void** previous) {
	wh_dllist_item_s* c = list->head; 
	u64 midpoint = (list->node_count + 2) / 2;

	// the go of scope
	if (index > list->node_count) {
		wh_log_error(("Index outside list range"));
		goto go_error_exit;
	}

	// TODO :: the tail code is off by one fix
	//if (index < midpoint) {
	while (0 < index--) {
		c = c->p_next;
	}
	/*} else {
		c = list->tail;
		index = list->node_count - (index);

		while (0 < index--) {
			c = c->p_previous;
		}
	}*/

	if (nullptr != c) {
		*previous = c->p_previous;
	}

	*current = c;
go_exit:
	return 0;

go_error_exit:
	*current = nullptr;
	*previous = nullptr;
	return -1;
}

static void* _wh_list_search_dll(_wh_list_search_params* params) {
	wh_dllist_item_s* node = params->list->head;

	while (nullptr != node) {
		if (!memcmp(node->data, params->ptr, params->list->type_size)) {
			return node;
		}

		node = node->p_next;
	}

	return nullptr;
}

#endif

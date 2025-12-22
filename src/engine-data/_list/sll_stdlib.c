#include<wh/data/list.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>

#include<string.h>
#include<stdlib.h>

#include"sll_common.c"

static void _wh_insert_sll_stdlib(_wh_sys_list_insert* params, void* current, void* previous) {
	wh_sllist_item_s* node = calloc(1, sizeof(wh_sllist_item_s));

	if (nullptr == node) {
		wh_log_error(("Failed to allocated node!"));
	}

	node->data = calloc(1, params->list->type_size);

	if (nullptr == node->data) {
		wh_log_error(("Failed to allocated node data!"));
	}

	memcpy(node->data, params->data, params->list->type_size);
	_wh_insert_sll(params, current, previous, node);
	wh_log_debug(("Inserted item into single std linked list!"));
}

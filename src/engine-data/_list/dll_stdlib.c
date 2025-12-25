#include<wh/data/list.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>

#include<string.h>
#include<stdlib.h>

#include"dll_common.c"

static i8 _wh_sys_list_double_stdlib_init(wh_list_s* out, _wh_sys_list_init_params* params) {
	wh_log_debug(("Hello!"));
	return 0;
}

static void _wh_push_back_dll_stdlib(_wh_list_push_back_params* params) {
	wh_dllist_item_s* node = malloc(sizeof(wh_dllist_item_s) + params->list->type_size);

	if (nullptr == node) {
		wh_log_error(("Failed to allocated node!"));
	}

	node->data = wh_ptr_add(node, sizeof(wh_dllist_item_s));
	memcpy(node->data, params->data, params->list->type_size);
	_wh_push_back_dll(params, node);
}


static void _wh_insert_dll_stdlib(_wh_sys_list_insert* params, void* current, void* previous) {
	wh_dllist_item_s* node = malloc(sizeof(wh_dllist_item_s) + params->list->type_size);

	if (nullptr == node) {
		wh_log_error(("Failed to allocated node!"));
	}

	node->data = wh_ptr_add(node, sizeof(wh_dllist_item_s));
	memcpy(node->data, params->data, params->list->type_size);
	_wh_insert_dll(params, current, previous, node);
}

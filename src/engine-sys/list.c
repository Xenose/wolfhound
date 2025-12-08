#include<wh/debug/logger.h>
#include<wh/data/list.h>

// Functions using the memory allocator
int8_t _wh_sys_llist_single_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_llist_double_init(wh_list_s* out, i64 list_type);
// Functions not using the memory allocator
int8_t _wh_sys_llist_single_memreq_init(wh_list_s* out, i64 list_type);
int8_t _wh_sys_llist_double_memreq_init(wh_list_s* out, i64 list_type);

int8_t (*_wh_internal_sys_llist_init_[])(wh_list_s* out, i64 list_type) = {
	&_wh_sys_llist_single_init
};

void _wh_sys_llist_double_add(wh_list_s* list, void* item) {
	wh_dllist_item_s* last = nullptr;

	if (nullptr == item) {
		wh_log_notice(("Pointless call to add for system linked list"));
		return;
	}

	if ((list->type_size + sizeof(wh_dllist_item_s)) > list->sysmem.free) {
		// TODO memory realloc
	}

	list->sysmem.free -= (list->type_size + sizeof(wh_dllist_item_s));
	last = list->tail;
}


/// Init blocks

int8_t _wh_sys_llist_single_init(wh_list_s* out, i64 list_type) {
	return 0;
}

int8_t _wh_sys_llist_double_init(wh_list_s* out, i64 list_type) {
	return 0;
}

wh_list_s _wh_sys_llist_init(i64 list_type, u64 type_size) {
	wh_list_s out = { 0 };

	out.stype = list_type;
	out.type_size = type_size;

	_wh_internal_sys_llist_init_[list_type - WH_STRUCT_TYPE_LLIST_SINGLE](&out, list_type);

	return out;
}

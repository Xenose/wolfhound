#include<wh/data/list.h>
#include<wh-data/list.h>
#include<wh/debug/logger.h>

#include<string.h>
#include<stdlib.h>

static i8 _wh_internal_sys_list_alloc_wolfhound(wh_list_s* out, u64 count) {
	void* new_data = nullptr;
	union {
		void* ptr;
		wh_sllist_item_s* sl;
		wh_dllist_item_s* dl;
	} node;

	switch(out->stype) {
		case WH_STRUCT_TYPE_LLIST_SYS_SINGLE:
			node.sl->p_next = new_data;
			break;
		case WH_STRUCT_TYPE_LLIST_SYS_DOUBLE:
			node.dl->p_next = new_data;
			break;
	}

	return 0;
}

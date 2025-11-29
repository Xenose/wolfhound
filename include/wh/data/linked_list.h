#ifndef _wh_header_data_linked_list_
#define _wh_header_data_linked_list_

#include<wh/common.h>
#include<wh/types/memory.h>

typedef struct _wh_sllist_item_s {
	struct _wh_sllist_item_s* p_next;
	void* data;
} wh_sllist_item_s;

typedef struct _wh_dllist_item_s {
	struct _wh_dllist_item_s* p_next;
	struct _wh_dllist_item_s* p_previous;
	void* data;
} wh_dllist_items_s;

typedef struct {
	struct_type stype;
	wh_heap_header_s heap;

	u64 type_size;

	void* head;
	void* tail;
} wh_list_s;

typedef struct {
	u64 type_size;
	u64 pre_items;
	wh_heap_header_s heap;
} _wh_init_params;

wh_list_s _wh_list_init(_wh_init_params params, ...);

#define wh_list_init(x, ...) WH_EPF(_wh_list_init((_wh_list_init_params) { \
	WH_VA_ARGS x } __VA_OPT__(__VA_ARGS__,) nullptr))

#endif /* _wh_header_data_linked_list_ */

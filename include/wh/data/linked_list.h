#ifndef _wh_header_data_linked_list_
#define _wh_header_data_linked_list_

#include<wh/common.h>
#include<wh/types/memory.h>

typedef struct _wh_linked_list_item_s{
	_wh_linked_list_item_s* pnext;
	wh_heap_header_s heap;
	void* data;
} wh_linked_list_item_s;

typedef struct {
	struct_type stype;

	u64 type_size;
	wh_linked_list_item_s* list;
} wh_linked_list_s;

typedef struct {
	u64 type_size;
	u64 pre_items;
	wh_heap_header_s heap;
} _wh_linked_list_init_params;

wh_linked_list_s _wh_linked_list_init(_wh_linked_list_init_params params, ...);

#define wh_linked_list_init(x, ...) WH_EPF(_wh_linked_list_init((_wh_linked_list_init_params) { \
	WH_VA_ARGS x } __VA_OPT__(__VA_ARGS__,) nullptr))

#endif /* _wh_header_data_linked_list_ */

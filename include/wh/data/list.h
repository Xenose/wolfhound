#ifndef _wh_header_data_linked_list_
#define _wh_header_data_linked_list_

#include<wh/common.h>
#include<wh/types/memory.h>
/*
typedef struct _wh_sllist_item_s {
	struct _wh_sllist_item_s* p_next;
	void* data;
} wh_sllist_item_s;

typedef struct _wh_dllist_item_s {
	struct _wh_dllist_item_s* p_next;
	struct _wh_dllist_item_s* p_previous;
	void* data;
} wh_dllist_item_s;

typedef struct {
	void* ptr;
	u64 size;
	u64 free;
} wh_sysmem_s;

typedef struct {
	struct_type stype;

	union {
		wh_heap_header_s heap;
		wh_sysmem_s sysmem;
	};

	u64 type_size;
	u64 node_count;

	void* head;
	void* tail;
} wh_list_s;

typedef struct {
	u64 type_size;
	u64 pre_items;
	wh_heap_header_s heap;
} _wh_list_init_params;

typedef struct {
	wh_list_s* list;
	u64 index;
} _wh_list_get_params;

typedef struct {
	wh_list_s* list;
	u64 index;
	void* ptr;
} _wh_list_insert_params;

typedef struct {
	wh_list_s* list;
	void* ptr;
} _wh_list_append_params;


wh_list_s _wh_list_init(_wh_list_init_params params, ...);

void* _wh_list_get(_wh_list_get_params params);

void _wh_list_insert(_wh_list_insert_params params, ...);
void _wh_list_append(_wh_list_append_params params, ...);

#define wh_list_init(x, ...) WH_EPF(_wh_list_init((_wh_list_init_params) { \
	WH_VA_ARGS x } __VA_OPT__(__VA_ARGS__,) nullptr))

#define wh_list_get(...) WH_EPF(_wh_list_get((_wh_list_get_params) { __VA_ARGS__ }))

#define wh_list_insert(x, ...) WH_EPF(_wh_list_insert((_wh_list_insert_params) { WH_VA_ARGS x }, __VA_ARGS__, nullptr)
#define wh_list_append(x, ...) WH_EPF(_wh_list_append((_wh_list_append_params) { WH_VA_ARGS x }, __VA_ARGS__, nullptr)
*/
#endif /* _wh_header_data_linked_list_ */

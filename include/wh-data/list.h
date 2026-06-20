#ifndef _wh_header_system_list_
#define _wh_header_system_list_

#include<wh-common/common.h>
#include<wh/data/list.h>

WH_C()

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
	wh_atomic_lock_s lock;

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
	wh_list_s* list;
	u64 index; 
} _wh_list_delete_params;

typedef struct {
	wh_list_s* list;
	u64 index; 
	void* data;
} _wh_list_insert_params;

typedef struct {
	wh_list_s* list;
	void* data;
} _wh_list_push_back_params;

typedef struct {
	wh_list_s* list;
	u64 index; 
} _wh_list_get_params;

typedef struct {
	wh_list_s* list;
	void* ptr;
} _wh_list_search_params;

typedef struct {
	wh_list_s* list;
	void* ptr;
	bool (*is_match)(void* ptr, void* user_data);
	u64* index;
} _wh_list_search_func_params;

typedef struct {
	wh_list_s* list;
	void (*do_func)(void* ptr, u64 index);
} _wh_list_for_each_params;

typedef struct {
	wh_list_s* list;
	void* node;
} _wh_list_data_params;

typedef struct {
	u64 type_size;
	u64 init_count;
} _wh_list_init_params;

extern void* _wh_list_get(_wh_list_get_params params);
extern i8 _wh_list_insert(_wh_list_insert_params params);
extern i8 _wh_list_push_back(_wh_list_push_back_params params);
extern void _wh_list_delete(_wh_list_delete_params params);

extern void* _wh_list_search(_wh_list_search_params params);
extern void* _wh_list_search_func(_wh_list_search_func_params params);
extern void _wh_list_for_each(_wh_list_for_each_params params);
extern void* _wh_list_data(_wh_list_data_params params);

extern wh_list_s _wh_list_init(i64 list_type, _wh_list_init_params params);

#define wh_dlist_init_memreq(...) _wh_list_init(WH_STRUCT_TYPE_LLIST_SYS_DOUBLE, (_wh_list_init_params) { __VA_ARGS__ })
#define wh_dlist_init_stdlib(...) _wh_list_init(WH_STRUCT_TYPE_LLIST_STD_DOUBLE, (_wh_list_init_params) { __VA_ARGS__ }) 

#define wh_list_get(_type_, ...) (_type_*)_wh_list_get((_wh_list_get_params) { __VA_ARGS__ })
#define wh_list_insert(...) _wh_list_insert((_wh_list_insert_params) { __VA_ARGS__ })
#define wh_list_push_back(...) _wh_list_push_back((_wh_list_push_back_params) { __VA_ARGS__ })
#define wh_list_delete(...) _wh_list_delete((_wh_list_delete_params) { __VA_ARGS__ })

#define wh_list_search(...) _wh_list_search((_wh_list_search_params) { __VA_ARGS__ })
#define wh_list_search_func(...) _wh_list_search_func((_wh_list_search_func_params) { __VA_ARGS__ })
#define wh_list_for_each(...) _wh_list_for_each((_wh_list_for_each_params) { __VA_ARGS__ })
#define wh_list_data(...) _wh_list_data((_wh_list_data_params) { __VA_ARGS__ })

//#define wh_list_add(list, in, index) sizeof(in) == list->type_size ? _wh_sys_list_add(list, index, in) : -1
//#define wh_list_push_back(list, in) sizeof(in) == list->type_size ? _wh_sys_list_push_back(list, in) : -1

//#define wh_list_get(list, out, index) sizeof(*out) == list->type_size ? (memcpy(out, _wh_sys_list_read(list, index), list->type_size)) : -1

WH_C_END()
#endif /* _wh_header_system_list_ */

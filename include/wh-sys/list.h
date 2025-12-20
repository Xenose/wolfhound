#ifndef _wh_header_system_list_
#define _wh_header_system_list_

#include<wh/common.h>
#include<wh/data/list.h>

WH_C()

typedef struct {
	u64 type_size;
	u64 init_count;
} _wh_sys_list_init_params;

extern wh_list_s _wh_sys_list_init(i64 list_type, _wh_sys_list_init_params params);

#define wh_dlist_init_memreq(...) _wh_sys_list_init(WH_STRUCT_TYPE_LLIST_SYS_DOUBLE, (_wh_sys_list_init_params) { __VA_ARGS__ })

#define wh_dlist_init_stdlib(...) _wh_sys_list_init(WH_STRUCT_TYPE_LLIST_STD_DOUBLE, (_wh_sys_list_init_params) { __VA_ARGS__ }) 

#define wh_list_add(list, in, index) sizeof(in) == list->type_size ? _wh_sys_list_add(list, index, in) : -1
#define wh_list_push_back(list, in) sizeof(in) == list->type_size ? _wh_sys_list_push_back(list, in) : -1

//#define wh_list_get(list, out, index) sizeof(*out) == list->type_size ? (memcpy(out, _wh_sys_list_read(list, index), list->type_size)) : -1

WH_C_END()
#endif /* _wh_header_system_list_ */

#ifndef _wh_header_system_list_
#define _wh_header_system_list_

#include<wh/common.h>
#include<wh/data/list.h>

WH_C()


extern wh_list_s _wh_sys_list_init(i64 list_type, u64 type_size);

#define wh_dlist_init_memreq(_type_) _wh_sys_list_init(WH_STRUCT_TYPE_LLIST_SYS_DOUBLE, sizeof(_type_))

#define wh_list_add(list, in, index) sizeof(in) == list->type_size ? _wh_sys_list_add(list, index, in) : -1
#define wh_list_push_back(list, in) sizeof(in) == list->type_size ? _wh_sys_list_push_back(list, in) : -1

//#define wh_list_get(list, out, index) sizeof(*out) == list->type_size ? (memcpy(out, _wh_sys_list_read(list, index), list->type_size)) : -1

WH_C_END()
#endif /* _wh_header_system_list_ */

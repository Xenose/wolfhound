#ifndef _wh_header_system_list_
#define _wh_header_system_list_

#include<wh/common.h>

WH_C()

#define wh_list_add(list, in, index) sizeof(in) == list->type_size ? _wh_sys_list_add(list, index, in) : -1
#define wh_list_push_back(list, in) sizeof(in) == list->type_size ? _wh_sys_list_push_back(list, in) : -1

#define wh_list_get(list, out, index) sizeof(*out) == list->type_size ? (memcpy(out, _wh_sys_list_read(list, index), list->type_size)) : -1

WH_C_END()
#endif /* _wh_header_system_list_ */

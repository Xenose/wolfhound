#ifndef _wh_header_sys_info_
#define _wh_header_sys_info_

#include<wh-core/common.h>

WH_C()

extern i64 wh_sys_gettid(void);
extern i64 wh_sys_program_path(char* buffer, u64 buffer_size);

WH_C_END()
#endif /* _wh_header_sys_info_ */

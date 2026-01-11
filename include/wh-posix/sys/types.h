#ifndef _wh_header_posix_sys_types_
#define _wh_header_posix_sys_types_

#include<wh-common/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_WINDOWS)
	typedef i64 pid_t;
	typedef i64 uid_t;
	typedef int useconds_t;
#endif

WH_C_END()
#endif /* _wh_header_posix_sys_types_ */

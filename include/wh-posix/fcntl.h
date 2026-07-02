#ifndef _wh_header_posix_fcntl_
#define _wh_header_posix_fcntl_

#include<wh-common/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<fcntl.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
#endif

#endif

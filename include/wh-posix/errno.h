#ifndef _wh_header_posix_errno_
#define _wh_header_posix_errno_

#include<wh-common/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<errno.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
#endif

#endif

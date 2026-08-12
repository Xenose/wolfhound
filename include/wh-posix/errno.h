#ifndef _wh_header_posix_errno_
#define _wh_header_posix_errno_

#include<wh-core/os.h>
#include<errno.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
#endif

#endif

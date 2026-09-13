#ifndef _wh_header_posix_execinfo_
#define _wh_header_posix_execinfo_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<execinfo.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
#endif

#endif

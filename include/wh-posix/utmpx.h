#ifndef _wh_header_posix_utmpx_
#define _wh_header_posix_utmpx_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<utmpx.h>
#endif

#endif /* _wh_header_posix_utmpx_ */

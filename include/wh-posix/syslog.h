#ifndef _wh_header_posix_syslog_
#define _wh_header_posix_syslog_

#include<wh-core/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<syslog.h>
#endif

WH_C_END()

#endif /* _wh_header_posix_syslog_ */

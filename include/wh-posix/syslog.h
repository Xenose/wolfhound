#ifndef _wh_header_posix_syslog_
#define _wh_header_posix_syslog_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<syslog.h>
#endif

#endif /* _wh_header_posix_syslog_ */

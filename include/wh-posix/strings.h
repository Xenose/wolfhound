#ifndef _wh_header_posix_strings_
#define _wh_header_posix_strings_

#include<wh-core/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<strings.h>
#endif

WH_C_END()

#endif /* _wh_header_posix_strings_ */

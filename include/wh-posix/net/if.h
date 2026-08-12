#ifndef _wh_header_posix_net_if_
#define _wh_header_posix_net_if_

#include<wh-core/os.h>

// For libc-test
#ifndef NI_NUMERICSCOPE
    #define NI_NUMERICSCOPE 0x0040
#endif

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<net/if.h>
#endif

#endif /* _wh_header_posix_net_if_ */

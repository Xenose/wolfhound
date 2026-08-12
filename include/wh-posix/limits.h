#ifndef _wh_header_posix_limits_
#define _wh_header_posix_limits_

#include<limits.h>
#include<wh-core/os.h>

// For libc-test
#ifndef _POSIX_UIO_MAXIOV
    #define _POSIX_UIO_MAXIOV 16
#endif

// For libc-test
#ifndef _XOPEN_IOV_MAX
    #define _XOPEN_IOV_MAX 16
#endif

// For libc-test
#ifndef _XOPEN_NAME_MAX
    #define _XOPEN_NAME_MAX 255
#endif

// For libc-test
#ifndef _XOPEN_PATH_MAX
    #define _XOPEN_PATH_MAX 1024
#endif

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<unistd.h>

    #ifndef NAME_MAX
        #define NAME_MAX 256
    #endif
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
    #ifndef NAME_MAX
        // Don't ask me about magic numbers...
        #define NAME_MAX 255
    #endif
#endif

#endif

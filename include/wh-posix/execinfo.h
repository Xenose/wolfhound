#ifndef _wh_header_posix_execinfo_
#define _wh_header_posix_execinfo_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<execinfo.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
    extern int backtrace(void *buffer, int size);
    extern char **backtrace_symbols(void *const buffer, int size);
    extern void backtrace_symbols_fd(void *const buffer, int size, int fd);
#endif

#endif

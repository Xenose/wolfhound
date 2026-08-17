#include<wh-posix/errno.h>
#include<wh-posix/string.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    #include"_windows/string.c"
#elif (WH_SYSTEM&WH_SYS_POSIX)
    #include"_posix/string.c"
#endif

// Cleaner then source code in this shim
#include"_common/string.c"

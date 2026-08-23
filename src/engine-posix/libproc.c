#include<wh-core/os.h>
#include<wh-posix/signal.h>

#if (WH_SYSTEM&WH_SYS_LINUX)
    #include"_common/libproc.c"
#endif

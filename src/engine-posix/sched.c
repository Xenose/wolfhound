#include<wh-core/os.h>
#include<wh-posix/sched.h>


#if (WH_SYSTEM&WH_SYS_WINDOWS)
    #include"_windows/sched.c"
#elif (WH_SYSTEM&WH_SYS_LINUX)
    #include"_linux/sched.c"
#endif

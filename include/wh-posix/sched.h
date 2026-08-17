#ifndef _wh_header_posix_sched_
#define _wh_header_posix_sched_

#include<wh-core/os.h>

#if (WH_SYSTEM&WH_SYS_LINUX)
    #include<sched.h>
#elif (WH_SYSTEM&WH_SYS_POSIX)
    #include<sched.h>
#else
    extern int clone(int (void* func_child), void* stack_top, int flags, void* args);
#endif


#endif /* _wh_header_posix_sched_ */

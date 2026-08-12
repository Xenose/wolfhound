#ifndef _wh_header_posix_sys_sem_
#define _wh_header_posix_sys_sem_

#include <wh-core/os.h>
#include <wh-posix/sys/types.h>
#include <wh-posix/sys/ipc.h>

#if (WH_SYSTEM & WH_SYS_POSIX)
    #include <sys/sem.h>
#endif

#endif /* _wh_header_posix_sys_sem_ */

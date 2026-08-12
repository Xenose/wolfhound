#ifndef _wh_header_posix_sys_types_
#define _wh_header_posix_sys_types_

#include<wh-posix/sys/types.h>
#include<wh-core/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    typedef i64 blkcnt_t;
    typedef i64 blksize_t;
    typedef i64 dev_t;
    typedef i64 gid_t;
    typedef i64 id_t;
    typedef i64 nlink_t;
    typedef i64 off_t;
    typedef i64 uid_t;
    typedef int mode_t;
    typedef int useconds_t;
    typedef intptr_t pid_t;
    typedef intptr_t ssize_t;
    typedef u64 fsblkcnt_t;
    typedef u64 fsfilcnt_t;
    typedef u64 ino_t;
#endif

WH_C_END()
#endif /* _wh_header_posix_sys_types_ */

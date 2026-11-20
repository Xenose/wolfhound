#ifndef _wh_header_posix_sys_types_
#define _wh_header_posix_sys_types_

#include<wh-core/os.h>
#include<wh-core/prefix.h>
#include<wh-posix/stdint.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    typedef int64_t blkcnt_t;
    typedef int64_t blksize_t;
    typedef int64_t dev_t;
    typedef int64_t gid_t;
    typedef int64_t id_t;
    typedef int64_t nlink_t;
    typedef int64_t off_t;
    typedef int64_t uid_t;
    typedef int mode_t;
    typedef int useconds_t;
    typedef intptr_t pid_t;
    typedef intptr_t ssize_t;
    typedef uint64_t fsblkcnt_t;
    typedef uint64_t fsfilcnt_t;
    typedef uint64_t ino_t;
#else
    #include<sys/types.h>
#endif

WH_C_END()

#endif /* _wh_header_posix_sys_types_ */

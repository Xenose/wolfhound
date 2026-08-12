#ifndef _wh_header_posix_fcntl_
#define _wh_header_posix_fcntl_

#include<wh-core/os.h>
#include<wh-posix/sys/types.h>

// For libc-test
#ifndef O_TTY_INIT
    #define O_TTY_INIT 0
#endif

// For libc-test
#ifndef O_EXEC
    #define O_EXEC     0
#endif

// For libc-test
#ifndef O_SEARCH
    #define O_SEARCH   0
#endif

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<fcntl.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)

    // Core flags
    #define O_RDONLY    0x000001
    #define O_WRONLY    0x000002
    #define O_RDWR      0x000003
    
    // Additional flags
    #define O_APPEND        0x000010
    #define O_ASYNC         0x000020
    #define O_CLOEXEC       0x000040
    #define O_CREAT         0x000080
    #define O_DIRECTORY     0x000100
    #define O_DSYNC         0x000200
    #define O_EXCL          0x000400
    #define O_LARGEFILE     0x000800
    #define O_NOATIME       0x001000
    #define O_NOCTTY        0x002000
    #define O_NOFOLLOW      0x004000
    #define O_NONBLOCK      0x008000
    #define O_NDELAY        O_NONBLOCK
    #define O_PATH          0x010000
    #define O_SYNC          0x020000
    #define O_TMPFILE       0x040000
    #define O_TRUNC         0x080000
    
    #define S_IRWXU         0x00700 // user (file owner) has read, write and execute permissions.
    #define S_IRUSR         0x00400 // user has read permissions.
    #define S_IWUSR         0x00200 // user has write permissions.
    #define S_IXUSR         0x00100 // user has execute permissions.
    
    #define S_IRWXG         0x00070 // group has read, write and execute permissions.
    #define S_IRGRP         0x00040 // group has read permissions.
    #define S_IWGRP         0x00020 // group has write permissions.
    #define S_IXGRP         0x00010 // group has execute permissions.
    
    #define S_IRWXO         0x00007 // others has read, write and execute permissions.
    #define S_IROTH         0x00004 // others has read permission.
    #define S_IWOTH         0x00002 // others has write permissions. 
    #define S_IXOTH         0x00001 // others has execute permissions.

    enum {
        // Duplicating a file descriptor
        F_DUPFD,
        F_DUPFD_CLOEXEC,
        // File descriptor flags
        F_GETFD,
        F_SETFD,
        // File status flags
        F_GETFL,
        F_SETFL,
        // Advisory record locking
        F_SETLK,
        F_SETLKW,
        F_GETLK,
        // Open file description locks (non-POSIX)
        F_OFD_SETLK,
        F_OFD_SETLKW,
        F_OFD_GETLK,
        // Managing signals
        F_GETOWN,
        F_SETOWN,
        F_GETOWN_EX,
        F_SETOWN_EX,
        F_GETSIG,
        F_SETSIG,
        // Leases
        F_SETLEASE,
        F_GETLEASE,
        // Delegations
        F_SETDELEG,
        F_GETDELEG,
        // File and directory change notification (dnotify)
        F_NOTIFY,
        // Changing the capacity of a pipe
        F_SETPIPE_SZ,
        F_GETPIPE_SZ,
        // File Sealing
        F_ADD_SEALS,
        F_GET_SEALS,
        // File read/write hints
        F_GET_RW_HINT,
        F_SET_RW_HINT,
        F_GET_FILE_RW_HINT,
        F_SET_FILE_RW_HINT,
    };
    
    extern int fcntl(int fd, int op, ...);
    extern int open(const char* path, int flags, mode_t mode);
    extern int create(const char* path, mode_t mode);
    extern int openat(int dirfd, const char* path, int flags, ...);
    
    // TODO Linux implementation
    // extern int openat2(int dirfd, const char* path, const struct open_how* how, size_t size);
#endif

#endif

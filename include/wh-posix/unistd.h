#ifndef _wh_header_wrap_unistd_
#define _wh_header_wrap_unistd_

#include<wh-core/common.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
    #include<unistd.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)

    enum {
        _SC_,
        _SC_ARG_MAX_,
        _SC_CHILD_MAX_,
        _SC_HOST_NAME_MAX_,
        _SC_LOGIN_NAME_MAX_,
        _SC_CLK_TCK_,
        _SC_OPEN_MAX_,
        _SC_PAGESIZE_,
        _SC_RE_DUP_MAX_,
        _SC_STREAM_MAX_,
        _SC_SYMLOOP_MAX_,
        _SC_TTY_NAME_MAX_,
        _SC_TZNAME_MAX_,
        _SC_VERSION_,
    
        // TODO posix 2
    };
    
    // _SC_XXX primary naming
    #define _SC_ARG_MAX				_SC_ARG_MAX_
    #define _SC_CHILD_MAX			_SC_CHILD_MAX_
    #define _SC_HOST_NAME_MAX		_SC_HOST_NAME_MAX_
    #define _SC_LOGIN_NAME_MAX	 	_SC_LOGIN_NAME_MAX_
    #define _SC_CLK_TCK				_SC_CLK_TCK_
    #define _SC_OPEN_MAX				_SC_OPEN_MAX_
    #define _SC_PAGESIZE 			_SC_PAGESIZE_
    #define _SC_RE_DUP_MAX			_SC_RE_DUP_MAX_
    #define _SC_STREAM_MAX			_SC_STREAM_MAX_
    #define _SC_SYMLOOP_MAX 		_SC_SYMLOOP_MAX_
    #define _SC_TTY_NAME_MAX		_SC_TTY_NAME_MAX_
    #define _SC_TZNAME_MAX			_SC_TZNAME_MAX_
    #define _SC_VERSION				_SC_VERSION_
    
    // _SC_XXX alt naming
    #define _SC_PAGE_SIZE _SC_PAGESIZE
    
    #define F_OK 0x0000
    #define R_OK 0x0001
    #define W_OK 0x0002
    #define X_OK 0x0004

    enum {
        SEEK_SET,
        SEEK_CUR,
        SEEK_END,
        SEEK_DATA,
        SEEK_HOLE,
    }

    extern int access(const char *path, int amode);
    extern int close(int fd);
    extern int dup(int oldfd);
    extern int getpagesize(void);
    extern int sleep(unsigned int seconds);
    extern int usleep(useconds_t usec);
    extern long sysconf(int name);
    extern off_t lseek(int fd, off_t offset, int whence);
    extern pid_t gettid(void);
    extern ssize_t write(int fd, const void* buffer, size_t count);
#endif

#ifndef _GNU_SOURCE
    extern pid_t gettid(void);
#endif

#endif /* _wh_header_wrap_unistd_ */

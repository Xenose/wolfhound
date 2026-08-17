#ifndef _wh_header_posix_sys_event_
#define _wh_header_posix_sys_event_

#include<wh-core/os.h>
#include<wh-posix/stdint.h>
#include<wh-posix/time.h>

#if !(WH_SYSTEM&WH_SYS_BSD)
    #define KQUEUE_CLOEXEC      0x0001
    #define KQUEUE_CPONFORK     0x0002

    // NetBSD macro
    #define O_CLOEXEC           KQUEUE_CLOEXEC 

    #define EV_ADD              0x00000001
    #define EV_ENABLE           0x00000002
    #define EV_DISABLE          0x00000004
    #define EV_DISPATCH         0x00000008

    #define EV_DELETE           0x00000010
    #define EV_RECEIPT          0x00000020
    #define EV_ONESHOT          0x00000040
    #define EV_CLEAR            0x00000080

    #define EV_EOF              0x00000100
    #define EV_ERROR            0x00000200
    #define EV_KEEPUDATE        0x00000400

    #define EVFILT_READ         0x00001000
    #define EVFILT_WRTIE        0x00002000
    #define EVFILT_EMPTY        0x00004000
    #define EVFILT_AIO          0x00008000

    #define EVFILT_VNODE        0x00010000
    #define EVFILT_PROC         0x00020000
    #define EVFILT_PROCDESC     0x00040000
    #define EVFILT_SIGNAL       0x00080000
    
    #define EVFILT_JAIL         0x00100000
    #define EVFILT_JAILDESC     0x00200000
    #define EVFILT_TIMER        0x00400000
    #define EVFILT_USER         0x00800000

    struct kevent {
        uintptr_t       ident;
        short           filter;
        unsigned short  flags;
        unsigned int    fflags;
        int64_t         data;
        void*           udata;
        uint64_t        ext[4];
    };

    extern int kqueue();
    extern int kqueuex(unsigned int flags);
    extern int kqueue1(int flags);
    
    extern int kevent(int kq, const struct kevent* changelist, int nchanges, struct kevent* eventlist, int nevents, const struct timespec* timeout);

    #define EV_SET(kev, ident, filters, flags, fflags, data, udata) // TODO
#else
    #include<sys/event.h>
#endif

#endif /* _wh_header_posix_sys_event_ */

#ifndef _wh_header_posix_sys_event_
#define _wh_header_posix_sys_event_

#include<wh-core/os.h>

#if !(WH_SYSTEM&WH_SYS_BSD)
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
    extern int kqueuex(p_int flags);
    extern int kqueue1(int flags);
    
    extern int kevent(int kg, const struct kevent* changelist, int nchanges, struct kevent* eventlist, int nevents, const struct timespec* timeout);

    #define EV_SET(kev, ident, filters, flags, fflags, data, udata) // TODO
#else
    #include<sys/event.h>
#endif

#endif /* _wh_header_posix_sys_event_ */

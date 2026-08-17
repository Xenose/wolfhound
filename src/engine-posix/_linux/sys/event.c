#include<sys/epoll.h>
#include<wh-posix/errno.h>
#include<wh-posix/sys/event.h>

int kqueue() {
    return kqueuex(0);
}
int kqueuex(unsigned int flags) {
    int _flags = 0;

    if (KQUEUE_CLOEXEC & flags) {
        _flags |= EPOLL_CLOEXEC;
    }

    return epoll_create1(_flags);
}
int kqueue1(int flags) {
    return kqueuex((unsigned int)flags);
}
    
int kevent(int kq, const struct kevent* changelist, int nchanges, struct kevent* eventlist, int nevents, const struct timespec* timeout) {
    struct epoll_event events[nevents] = { };
 
    if (0 > kq) {
        errno = EBADF;
        goto go_error_exit;
    }

    // return results right away
    if (0 == nevents) {
        goto go_exit;
    }
    
    epoll_pwait2(kq, events, nchanges, timeout, 0);

    //if (EVFILT_SIGNAL & 
    
go_exit:
    return 0;
go_error_exit:
    return -1;
}

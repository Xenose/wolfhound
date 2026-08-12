#include <wh-sys/atomic_lock.h>

int _wh_clear_lock_flags(wh_atomic_lock_s* x) {
    x->thread_id = 0;
    x->nested = 0;
    x->pre_nested = 0;
    atomic_flag_clear(&x->locked);
    return 0;
}

pid_t _wh_spinlock_blocker(wh_atomic_lock_s* lock) {
    pid_t tid = wh_sys_gettid();

    if (tid == lock->thread_id) {
        goto go_skip_lock;
    }

    while (atomic_flag_test_and_set(&lock->locked));
go_skip_lock:

    return tid;
}

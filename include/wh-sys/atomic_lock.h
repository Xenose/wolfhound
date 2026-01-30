#ifndef _wh_header_common_spinlock_
#define _wh_header_common_spinlock_

#include<wh-common/common.h>
#include<wh-sys/info.h>
#include<wh-posix/unistd.h>

WH_C()

typedef struct {
	atomic_flag locked;

	i64 thread_id;
	i64 pre_nested;
	i64 nested;
} wh_atomic_lock_s;

extern int _wh_clear_lock_flags(wh_atomic_lock_s* x);
extern pid_t _wh_spinlock_blocker(wh_atomic_lock_s* lock);

#define wh_spinlock_v3(_x_) \
	for ((_x_)->thread_id = _wh_spinlock_blocker(_x_), (_x_)->pre_nested = (_x_)->nested, (_x_)->nested++; \
		(_x_)->pre_nested != (_x_)->nested; 0 >= --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0)

#define wh_unlock(_x_) 0 >= --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0

WH_C_END()

#endif /* _wh_header_common_spinlock_ */

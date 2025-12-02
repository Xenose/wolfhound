#ifndef _wh_header_common_spinlock_
#define _wh_header_common_spinlock_

#include<wh/common.h>
#include <pthread.h>
#include<wh-posix/unistd.h>

typedef struct {
	atomic_flag locked;

	pthread_t thread_id;
	i64 pre_nested;
	i64 nested;
} wh_atomic_lock_s;

static inline int _wh_clear_lock_flags(wh_atomic_lock_s* x) {
	x->thread_id = 0;
	atomic_flag_clear(&x->locked);
	return 0;
}

// Note to self single line if's not supported
#define wh_spinlock_v2(_x_) \
	while (atomic_flag_test_and_set(&(_x_)->locked) && (_x_)->nested ? pthread_self() != (_x_)->thread_id : 0 != (_x_)->thread_id) { } \
	for ((_x_)->thread_id = (0 == (_x_)->thread_id ? pthread_self() : (_x_)->thread_id), (_x_)->pre_nested = (_x_)->nested, (_x_)->nested++; \
		(_x_)->pre_nested != (_x_)->nested ; \
		0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0)

#define wh_lock_break(_x_)				0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; break
#define wh_lock_return(_x_, ...)		0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; return __VA_ARGS__
#define wh_lock_goto(_x_, _goto_)	0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; goto _goto_


#endif /* _wh_header_common_spinlock_ */

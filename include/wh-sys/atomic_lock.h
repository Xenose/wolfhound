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



#if (WH_SYSTEM&WH_SYS_TCC)
	#define wh_spin_lock_break(_x_) break
	#define wh_spin_lock_return(_x_, _return_) return _return_
	#define wh_spin_lock_goto(_x_, _goto_) goto _goto_


	#define wh_spinlock(_x_)

	#define wh_spinlock_break(_x_) break
	#define wh_spinlock_return(_x_, ...) return __VA_ARGS__
	#define wh_spinlock_goto(_x_, _goto_) goto _goto_

#else
	#define wh_spin_lock_break(_x_)					atomic_flag_clear(_x_); break
	#define wh_spin_lock_return(_x_, _return_)	atomic_flag_clear(_x_);	return _return_
	#define wh_spin_lock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_


	#define wh_spinlock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

	#define wh_spinlock_break(_x_)				atomic_flag_clear(_x_); break
	#define wh_spinlock_return(_x_, ...)		atomic_flag_clear(_x_);	return __VA_ARGS__
	#define wh_spinlock_goto(_x_, _goto_)		atomic_flag_clear(_x_);	goto _goto_
#endif

// DEPRECATED USE V3 historical reference.
#define wh_spin_lock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

// DEPRECATED USE V3 historical reference.
// Note to self single line if's, for's, while's not supported
/* #define wh_spinlock_v2(_x_) \
 * while (atomic_flag_test_and_set(&(_x_)->locked) && wh_sys_gettid() != (_x_)->thread_id) { } \
 * for ((_x_)->thread_id = wh_sys_gettid(), (_x_)->pre_nested = (_x_)->nested, (_x_)->nested++; \
 * (_x_)->pre_nested != (_x_)->nested; 0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0)
 */

#define wh_spinlock_v3(_x_) \
	for ((_x_)->thread_id = _wh_spinlock_blocker(_x_), (_x_)->pre_nested = (_x_)->nested, (_x_)->nested++; \
		(_x_)->pre_nested != (_x_)->nested; 0 >= --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0)

#define wh_unlock(_x_) 0 >= --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0

//#define wh_lock_break(_x_)				0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; break
//#define wh_lock_return(_x_, ...)		0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; return __VA_ARGS__
//#define wh_lock_goto(_x_, _goto_)	0 == --(_x_)->nested ? _wh_clear_lock_flags(_x_) : 0; goto _goto_

WH_C_END()
#endif /* _wh_header_common_spinlock_ */

#ifndef _wh_header_common_macros_
#define _wh_header_common_macros_

#include<wh/common/prefix.h>

WH_C()

#define WH_VA_ARGS(...) __VA_ARGS__

#define wh_not(_x_) !(_x_)
#define wh_ptr_add(_ptr_, _x_) ((void*)(((char*)_ptr_) + _x_))
#define wh_ptr_sub(_ptr_, _x_) ((void*)(((char*)_ptr_) - _x_))

/* [MD_DOC]
 * wh_for is a macro for a for loop, it will go from 0
 * to the given end point.
 */
#define wh_for(_type_, _index_, _count_) for (_type_ _index_ = 0; (_index_) < (_count_); (_index_)++)

#define wh_ptr_assign(_ptr_, _value_) if (nullptr != _ptr_) *_ptr = _value_

#define wh_spin_lock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

#define wh_spin_lock_break(_x_)					atomic_flag_clear(_x_); break
#define wh_spin_lock_return(_x_, _return_)	atomic_flag_clear(_x_);	return _return_
#define wh_spin_lock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
	#define wh_thread _Thread_local
#else
	#define wh_thread __thread
#endif

WH_C_END()
#endif /* _wh_header_common_macros_ */

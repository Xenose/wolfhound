#ifndef _wh_header_common_macros_
#define _wh_header_common_macros_

#include<stddef.h>

#include<wh-common/os.h>
#include<wh-common/prefix.h>
#include<wh-common/c23-comp.h>

WH_C()

#define WH_PTR_MAX ((void*)-1)
#define WH_VA_ARGS(...) __VA_ARGS__

#define wh_ptr_assign(_ptr_, _value_) if (nullptr != _ptr_) *_ptr_ = _value_
#define wh_not(_x_) !(_x_)
#define wh_ptr_add(_ptr_, _x_) ((void*)(((char*)_ptr_) + _x_))
#define wh_ptr_sub(_ptr_, _x_) ((void*)(((char*)_ptr_) - _x_))

#ifndef __FILENAME__
	#define __FILENAME__ __FILE__
#endif

// WH_EPF :: Empty Parameter Function
#if !(WH_SYSTEM&WH_SYS_GCC)&&!(WH_SYSTEM&WH_SYS_MINGW)&&!(WH_SYSTEM&WH_SYS_MSVC)&&!(WH_SYSTEM&WH_SYS_TCC)
	#define WH_EPF(x) \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wmissing-field-initializers\"") \
		x \
		_Pragma("GCC diagnostic pop")
#else
	#define WH_EPF(x) \
		x
#endif

/* [MD_DOC]
 * wh_for is a macro for a for loop, it will go from 0
 * to the given end point.
 */
#define wh_for(_type_, _index_, _count_) for (_type_ _index_ = 0; (_index_) < (_count_); (_index_)++)

#define wh_spin_lock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

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

	#define wh_spinlock_break(_x_)					atomic_flag_clear(_x_); break
	#define wh_spinlock_return(_x_, ...)		atomic_flag_clear(_x_);	return __VA_ARGS__
	#define wh_spinlock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_
#endif

WH_C_END()
#endif /* _wh_header_common_macros_ */

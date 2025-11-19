#ifndef _wh_header_common_macros_
#define _wh_header_common_macros_

#include <stddef.h>
#include<wh/common/prefix.h>

WH_C()

#define WH_PTR_MAX ((void*)-1)
#define WH_VA_ARGS(...) __VA_ARGS__

#define wh_ptr_assign(_ptr_, _value_) if (nullptr != _ptr_) *_ptr_ = _value_
#define wh_not(_x_) !(_x_)
#define wh_ptr_add(_ptr_, _x_) ((void*)(((char*)_ptr_) + _x_))
#define wh_ptr_sub(_ptr_, _x_) ((void*)(((char*)_ptr_) - _x_))

#define WH_SYS_UNIX		0x01
#define WH_SYS_POSIX		0x02
#define WH_SYS_GCC		0x04
#define WH_SYS_CLANG		0x08
#define WH_SYS_MSVC		0x10

#define WH_SYS_LINUX		(0x100 | WH_SYS_UNIX | WH_SYS_POSIX)
#define WH_SYS_FREEBSD	(0x200 | WH_SYS_UNIX | WH_SYS_POSIX)
#define WH_SYS_MACOS		(0x400 | WH_SYS_UNIX | WH_SYS_POSIX)

#define WH_SYS_WINDOWS	(0x800)

#if defined(__linux__)
	#define WH_SYSTEM_OS WH_SYS_LINUX
#elif defined(_WIN32)
	#define WH_SYSTEM_OS WH_SYS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#define WH_SYSTEM_OS WH_SYS_MACOS
#elif defined(__FreeBSD__)
	#define WH_SYSTEM_OS WH_SYS_FREEBSD
#elif defined(__unix__)
	#ifdef _POSIX_C_SOURCE
		#define WH_SYSTEM_OS (WH_SYS_UNIX | WH_SYS_POSIX)
	#else
		#define WH_SYSTEM_OS WH_SYS_UNIX 
	#endif
#endif

#ifdef __clang__
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_CLANG)
#elif defined(__GNUC__)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_GCC)
#elif defined(_MSC_VER)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_MSVC)
#else
    #error "Unknown OS: Please add support for your platform to WH_SYSTEM_OS"
#endif

#ifndef __FILENAME__
	#define __FILENAME__ __FILE__
#endif

#if !defined(__cplusplus)
	#if !defined(nullptr) && (__STDC_VERSION__ < 202000L)
		#define nullptr NULL
	#endif
#endif

/* [MD_DOC]
 * wh_for is a macro for a for loop, it will go from 0
 * to the given end point.
 */
#define wh_for(_type_, _index_, _count_) for (_type_ _index_ = 0; (_index_) < (_count_); (_index_)++)

#define wh_spin_lock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

#define wh_spin_lock_break(_x_)					atomic_flag_clear(_x_); break
#define wh_spin_lock_return(_x_, _return_)	atomic_flag_clear(_x_);	return _return_
#define wh_spin_lock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_


#define wh_spinlock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

#define wh_spinlock_break(_x_)					atomic_flag_clear(_x_); break
#define wh_spinlock_return(_x_, ...)		atomic_flag_clear(_x_);	return __VA_ARGS__
#define wh_spinlock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_

/*
 * After C11 it seems like there is a keyword
 * wolfhound is built for C23, but this macro
 * cost me nothing so I would say its worth
 * the extra macro.
 */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
	#define wh_thread _Thread_local
#else
	#define wh_thread __thread
#endif

WH_C_END()
#endif /* _wh_header_common_macros_ */

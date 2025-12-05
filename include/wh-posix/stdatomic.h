#ifndef _wh_posix_stdatomic_
#define _wh_posix_stdatomic_

#include<stdint.h>
#include<wh-common/os.h>
#include<wh-common/macros.h>

#define __STDC_NO_ATOMICS__ // for compiler highlight remove later
	

#if (WH_SYSTEM&WH_SYS_TCC) || defined(__STDC_NO_ATOMICS__)
	#define WH_USE_ATOMIC 1

	typedef volatile char atomic_char;
	typedef volatile _Bool atomic_flag;
	typedef volatile _Bool atomic_bool;

	typedef volatile int8_t atomic_int_fast8_t;
	typedef volatile int16_t atomic_int_fast16_t;
	typedef volatile int32_t atomic_int_fast32_t;
	typedef volatile int64_t atomic_int_fast64_t;

	extern _Bool atomic_flag_test_and_set(atomic_flag* flag);
	extern void atomic_flag_clear(atomic_flag* flag);

	#define atomic_load(ptr) \
		_Generic(*(ptr), \
				int8_t: atomic_load_int8_t, \
				int16_t: atomic_load_int16_t, \
				int32_t: atomic_load_int32_t, \
				int64_t: atomic_load_int64_t, \
				default: atomic_load_unsupported \
		)(ptr)
#else
	#include<stdatomic.h>
#endif 

#endif /* _wh_posix_stdatomic_ */

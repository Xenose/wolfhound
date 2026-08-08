#ifndef _wh_posix_stdatomic_
#define _wh_posix_stdatomic_

#include<wh-posix/stdint.h>

#include<wh-core/c23-comp.h>
#include<wh-core/macros.h>
#include<wh-core/os.h>

//#define __STDC_NO_ATOMICS__ // for compiler highlight remove later

#ifndef __cplusplus
    #if (defined(__STDC_NO_ATOMICS__) || (WH_SYSTEM&WH_SYS_TCC)) && !(WH_SYSTEM&WH_SYS_MINGW) 
        typedef volatile char atomic_char;
        typedef volatile int8_t atomic_flag;
        typedef volatile int8_t atomic_bool;

        typedef volatile signed char atomic_schar;
        typedef volatile short atomic_short;
        typedef volatile int atomic_int;
        typedef volatile long atomic_long;
        typedef volatile long long atomic_llong;

        typedef volatile unsigned char atomic_uchar;
        typedef volatile unsigned short atomic_ushort;
        typedef volatile unsigned int atomic_uint;
        typedef volatile unsigned long atomic_ulong;
        typedef volatile unsigned long long atomic_ullong;

        //typedef volatile char8_t atomic_char8_t;
        //typedef volatile char16_t atomic_char16_t;
        //typedef volatile char32_t atomic_char32_t;
        typedef volatile wchar_t atomic_wchar_t;

        typedef volatile int8_t atomic_int_fast8_t;
        typedef volatile int16_t atomic_int_fast16_t;
        typedef volatile int32_t atomic_int_fast32_t;
        typedef volatile int64_t atomic_int_fast64_t;

        typedef volatile int8_t atomic_int_least8_t;
        typedef volatile int16_t atomic_int_least16_t;
        typedef volatile int32_t atomic_int_least32_t;
        typedef volatile int64_t atomic_int_least64_t;

        typedef volatile uint8_t atomic_uint_fast8_t;
        typedef volatile uint16_t atomic_uint_fast16_t;
        typedef volatile uint32_t atomic_uint_fast32_t;
        typedef volatile uint64_t atomic_uint_fast64_t;

        typedef volatile uint8_t atomic_uint_least8_t;
        typedef volatile uint16_t atomic_uint_least16_t;
        typedef volatile uint32_t atomic_uint_least32_t;
        typedef volatile uint64_t atomic_uint_least64_t;

        typedef volatile intptr_t atomic_intptr_t;
        typedef volatile uintptr_t atomic_uintptr_t;
        typedef volatile size_t atomic_size_t;
        typedef volatile ptrdiff_t atomic_ptrdiff_t;
        typedef volatile intmax_t atomic_intmax_t;
        typedef volatile uintmax_t atomic_uintmax_t;

        /*
         * Defined in XXX_XX_stdatomic.asm
         */
        extern int8_t atomic_flag_test_and_set(atomic_flag* flag);
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
#else
    #include<atomic>

    typedef std::atomic_int_least8_t atomic_int_least8_t;
    typedef std::atomic_int_least16_t atomic_int_least16_t;
    typedef std::atomic_int_least32_t atomic_int_least32_t;
    typedef std::atomic_int_least64_t atomic_int_least64_t;

    typedef std::atomic_uint_least8_t atomic_uint_least8_t;
    typedef std::atomic_uint_least16_t atomic_uint_least16_t;
    typedef std::atomic_uint_least32_t atomic_uint_least32_t;
    typedef std::atomic_uint_least64_t atomic_uint_least64_t;

    typedef std::atomic_flag atomic_flag;
    typedef std::atomic_bool atomic_bool;
#endif /* __cplusplus */
#endif /* _wh_posix_stdatomic_ */

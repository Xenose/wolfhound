#ifndef _wh_header_wrap_atomic_
#define _wh_header_wrap_atomic_

#ifndef __cplusplus
#include<stdatomic.h>
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
#endif /* _wh_header_wrap_atomic_ */

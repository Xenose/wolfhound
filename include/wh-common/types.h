#ifndef _wh_header_common_types_
#define _wh_header_common_types_

#include<wh-posix/stdint.h>
#include<wh-posix/stdatomic.h>

/* [MD_DOC]
 * # Integer Types
 * 
 * | Name     | Type       | Comment                              |
 * | -------- | ---------- | ------------------------------------ |
 * | int128_t | __int128_t | Using the compiler in built integer. |
 * | i8       | int8_t     |                                      |
 * | i16      | int16_t    |                                      |
 * | i32      | int32_t    |                                      |
 * | i64      | int64_t    |                                      |
 * | i128     | int128_t   |                                      |
 */

#if defined(_MSC_VER) || defined(__TINYC__)
	typedef int64_t	int128_t;
	typedef uint64_t	uint128_t;
#else
	typedef __int128_t	int128_t;
	typedef __uint128_t	uint128_t;
#endif

typedef int8_t		i8;
typedef int16_t	i16;
typedef int32_t	i32;
typedef int64_t	i64;
typedef int128_t	i128;

typedef uint8_t	u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef uint128_t	u128;

typedef atomic_int_least8_t	ai8;
typedef atomic_int_least16_t	ai16;
typedef atomic_int_least32_t	ai32;
typedef atomic_int_least64_t	ai64;

typedef atomic_uint_least8_t	au8;
typedef atomic_uint_least16_t	au16;
typedef atomic_uint_least32_t	au32;
typedef atomic_uint_least64_t	au64;

typedef atomic_flag aflag;
typedef atomic_bool abool;

//typedef _Atomic(void*) atomic_void_ptr;

typedef i64 struct_type;

#endif /* _wh_header_common_types_ */

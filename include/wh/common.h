#ifndef _wh_header_common_
#define _wh_header_common_

#include<limits.h>

#include<wh/common/prefix.h>
#include<wh/common/bytes.h>
#include<wh/common/enum.h>
#include<wh/common/macros.h>
#include<wh/wrap/atomic.h>

WH_C()

#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>

#if !(WH_SYSTEM&WH_SYS_WINDOWS)
	#include<sys/types.h>
#endif

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

#ifdef _MSC_VER
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

/* [MD_DOC]
 * ## wh_string_s
 * This is a safe string that doesn't really on nullptr termination
 * and instead uses length to keep track of its length.
 *
 * | Variable | Type     | Comment                                                                                      |
 * | -------- | -------- | -------------------------------------------------------------------------------------------  |
 * | data     | uint8_t* | This variable is for accessing the bytes directly its in the shared memory with str and ptr. |
 * | str      | char*    | This variable is for accessing the string directly, it shares memory with data and ptr.      |
 * | ptr      | void*    | This variable is for accessing the pointer directly, it shares memory with str and data.     |
 * | length   | uint64_t | The length of the stored data.                                                               |
 */
typedef struct {
	union {
		u8* data;
		char* str;
		void* ptr;
	};
	u64 length;
} wh_string_s;

typedef struct {
	u64 r : 8;
	u64 g : 8;
	u64 b : 8;
	u64 a : 8;
} wh_rgba_s;

typedef struct {
	u64 bytes;
	void* ptr;
} wh_buffer_s;

#ifndef NAME_MAX
#define NAME_MAX 256
#endif

typedef struct {
	struct_type stype;
} wh_struct;

WH_C_END()
#endif /* _wh_header_common_ */

#ifndef _wh_header_common_
#define _wh_header_common_

#include<limits.h>
#include<wh/common/prefix.h>

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

WH_C()

#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>


#ifndef _WIN32
#include<sys/types.h>
#endif

#define WH_VA_ARGS(...) __VA_ARGS__

#ifndef _WIN32
enum {
	STRUNCATE = 10'000
};
#endif

#define WH_64B		64
#define WH_128B	128
#define WH_256B	256
#define WH_512B	512

#define WH_1KB		1'024
#define WH_2KB		2'048
#define WH_4KB		4'096
#define WH_8KB		8'192
#define WH_16KB	16'384
#define WH_32KB	32'768
#define WH_64KB	65'536
#define WH_128KB	131'072
#define WH_256KB	262'144
#define WH_512KB	524'288

#define WH_1MB		1'048'576
#define WH_2MB		2'097'152
#define WH_4MB		4'194'304
#define WH_8MB		8'388'608
#define WH_16MB	16'777'216
#define WH_32MB	33'554'432
#define WH_64MB	67'108'864
#define WH_128MB	134'217'728
#define WH_256MB	268'425'456
#define WH_512MB	536'830'912

#define WH_1GB		1'073'661'824
#define WH_2GB		2'147'323'648

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

#ifdef _MSVC
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

#define wh_not(_x_) !(_x_)
#define wh_ptr_add(_ptr_, _x_) ((void*)(((char*)_ptr_) + _x_))
#define wh_ptr_sub(_ptr_, _x_) ((void*)(((char*)_ptr_) - _x_))

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
	#define wh_thread _Thread_local
#else
	#define wh_thread __thread
#endif

/* [MD_DOC]
 * wh_for is a macro for a for loop, it will go from 0
 * to the given end point.
 */
#define wh_for(_type_, _index_, _count_) for (_type_ _index_ = 0; (_index_) < (_count_); (_index_)++)

#define wh_ptr_assign(ptr, value) if (nullptr != ptr) *ptr = value

#define wh_spin_lock(_x_) do {} while (atomic_flag_test_and_set(_x_)); for (i8 _lock_##__LINE__ = 0; 1 != _lock_##__LINE__; _lock_##__LINE__++, atomic_flag_clear(_x_))

#define wh_spin_lock_break(_x_)					atomic_flag_clear(_x_); break
#define wh_spin_lock_return(_x_, _return_)	atomic_flag_clear(_x_);	return _return_
#define wh_spin_lock_goto(_x_, _goto_)			atomic_flag_clear(_x_);	goto _goto_

#ifndef NAME_MAX
#define NAME_MAX 256
#endif

enum {
	WH_STRUCT_TYPE_UNKOWN = 0,

	WH_TYPE_I64,
	WH_TYPE_U64,
	WH_TYPE_FLOAT,
	WH_TYPE_DOUBLE,
	WH_TYPE_BOOL,
	WH_TYPE_STRING,
	WH_TYPE_FUNCTION_PTR,

	WH_STRUCT_TYPE_INSTANCE,

	WH_STRUCT_TYPE_HEAP_ARENA,
	WH_STRUCT_TYPE_HEAP_BUCKET,
	WH_STRUCT_TYPE_HEAP_FREELIST,
	WH_STRUCT_TYPE_HEAP_STACK,
	WH_STRUCT_TYPE_HEAP_NODE,

	WH_STRUCT_TYPE_IMG_PNG,
	WH_STRUCT_TYPE_IMG_JPEG,

	WH_STRUCT_TYPE_ENUM_END
};

enum {
	WH_SUCCESS,
	WH_ERROR_UNKOWN,

	WH_ERROR_INVALID_PARAM,
	WH_ERROR_INVALID_PARAM_NULLPTR,
	WH_ERROR_FAILED_MEMREQ,
	WH_ERROR_HEAP_TOO_SMALL,
	WH_ERROR_NO_MATCH,
	WH_ERROR_NO_MEMORY,
	WH_ERROR_OVERFLOW_ISSUE,

	WH_ERROR_ENUM_END
};

typedef struct {
	struct_type stype;
} wh_struct;

WH_C_END()
#endif /* _wh_header_common_ */

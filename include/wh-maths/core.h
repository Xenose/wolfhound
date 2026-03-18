#ifndef _wh_header_maths_core_
#define _wh_header_maths_core_

#include<math.h>
#include<stdlib.h>

#include<wh-common/common.h>
#include<wh/params/math.h>

WH_C()

extern i64 _wh_c_intpos(_wh_intpos_params params);
extern u64 _wh_uintpos(_wh_uintpos_params params);

extern i64 _wh_intpos(_wh_intpos_params params);
extern i128 _wh_intpos128(_wh_intpos128_params params);

extern i64 _wh_intpow(_wh_intpow_params params);
extern i64 _wh_hash_simple(_wh_hash_simple_params params);

#define wh_c_intpos(...) WH_EPF(_wh_c_intpos((_wh_intpos_params){ __VA_ARGS__ }))

#define wh_intpos(...)	WH_EPF(_wh_intpos((_wh_intpos_params){ __VA_ARGS__ }))
#define wh_intpos128(...) WH_EPF(_wh_intpos128((_wh_intpos128_params){ __VA_ARGS__ }))

#define wh_uintpos(...)	WH_EPF(_wh_uintpos((_wh_uintpos_params){ __VA_ARGS__ }))
#define wh_intpow(...)	WH_EPF(_wh_intpow((_wh_intpow_params){ __VA_ARGS__ }))

// wh_abs macros as we need to support C++ as well,
// this allows us to use them in C++ templates.
#define WH_ABS_I8(x)   ((x) ^ ((x) >> 7)) - ((x) >> 7)
#define WH_ABS_I16(x)  ((x) ^ ((x) >> 15)) - ((x) >> 15)
#define WH_ABS_I32(x)  ((x) ^ ((x) >> 31)) - ((x) >> 31)
#define WH_ABS_I64(x)  ((x) ^ ((x) >> 63)) - ((x) >> 63)
#define WH_ABS_I128(x) ((x) ^ ((x) >> 127)) - ((x) >> 127)

/* [MD_DOC]
 * # wh_abs
 * This function is a non branching abs functions for signed and
 * unsigned integers, for float and doubles the normal abs from
 * maths.h is called.
 *
 * ## MSVC note
 * MSVC for some reason don't support _Generic meaning we just
 * brute force it with fabs....
 *
 * ## Return value
 * Returns a positive value from the original value, the minimum
 * values will return -128 as 1000 0000 or -128 in int8_t will result
 * in 1000 0000 this is a limitation of how integers are represented.
 */
#if (WH_SYSTEM&WH_SYS_MSVC)
	// MSVC a inferior compiler...
	// C++ compiler claiming C11 support...
	// Note :: unsigned integers will be matched on size.
	#define wh_abs(x) ( \
		sizeof(x) == 1 ? WH_ABS_I8((i8)x) : \
		sizeof(x) == 2 ? WH_ABS_I16((i16)x) : \
		sizeof(x) == 4 ? WH_ABS_I32((i32)x) : \
		sizeof(x) == 8 ? WH_ABS_I64((i64)x) : \
		fabs((float)x) \
	)
#elif (WH_SYSTEM&WH_SYS_TCC)
	#define wh_abs(x) \
		_Generic((x), \
			i8: WH_ABS_I8(x), \
			i16: WH_ABS_I16(x), \
			i32: WH_ABS_I32(x), \
			i64: WH_ABS_I64(x), \
			u8: (x), \
			u16: (x), \
			u32: (x), \
			u64: (x), \
			default: labs(x) \
			)
#else
	#define wh_abs(x) \
		_Generic((x), \
			i8: WH_ABS_I8(x), \
			i16: WH_ABS_I16(x), \
			i32: WH_ABS_I32(x), \
			i64: WH_ABS_I64(x), \
			i128: WH_ABS_I128(x), \
			u8: (x), \
			u16: (x), \
			u32: (x), \
			u64: (x), \
			u128: (x), \
			default: fabsl((long double)x) \
			)
#endif

/* [MD_DOC]
 * # wh_hash_simple
 * ```c
 *	int64_t wh_hash_simple(const char* str, u64 limit, u64 length : optional)
 * ```
 *
 * | Parameter     | Optional  | Type     | Designation | Description                     |
 * | ------------- | --------- | -------- | ----------- | ------------------------------- |
 * | string        | NO        | char*    | .str        | The string that will be hashed. |
 * | slot limit    | NO        | uint64_t | .limit      | The limit of slots.             |
 * | string length | YES       | uint64_t | .length     | The length of the string        |
 *
 * ## Return value
 *
 */
#define wh_hash_simple(...) WH_EPF(_wh_hash_simple((_wh_hash_simple_params){ __VA_ARGS__ }))


#ifdef USE_NAMESPACE_STD_WOLFHOUND
#define wh_abs abs
#endif /* USE_NAMESPACE_STD_WOLFHOUND */

#ifdef USE_NAMESPACE_WOLFHOUND
#define int_dec_count wh_int_dec_count
#define intpow wh_intpow
#define hash_simple wh_hash_simple
#endif /* USE_NAMESPACE_WOLFHOUND */

WH_C_END()

#endif /* _wh_header_maths_core_ */

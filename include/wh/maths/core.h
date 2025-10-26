#ifndef _wh_header_maths_core_
#define _wh_header_maths_core_

#include<wh/common.h>
#include<wh/params/math.h>

extern i64 _wh_intlog(_wh_intlog_params params);
extern i64 _wh_intpow(_wh_intpow_params params);
extern i64 _wh_hash_simple(_wh_hash_simple_params params);

#define wh_intlog(...) _wh_intlog((_wh_intlog_params){ __VA_ARGS__ })
#define wh_intpow(...) _wh_intpow((_wh_intpow_params){ __VA_ARGS__ })


#define wh_abs(x) \
_Generic((x), \
	i8: ((x) ^ ((x) >> 7)) - ((x) >> 7), \
	i16: ((x) ^ ((x) >> 15)) - ((x) >> 15), \
	i32: ((x) ^ ((x) >> 31)) - ((x) >> 31), \
	i64: ((x) ^ ((x) >> 63)) - ((x) >> 63), \
	i128: ((x) ^ ((x) >> 127)) - ((x) >> 127), \
	u8: (x), \
	u16: (x), \
	u32: (x), \
	u64: (x), \
	u128: (x), \
	default: abs(x) \
	)

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
#define wh_hash_simple(...) _wh_hash_simple((_wh_hash_simple_params){ __VA_ARGS__ })


#ifdef USE_NAMESPACE_STD_WOLFHOUND
#define wh_abs abs
#endif /* USE_NAMESPACE_STD_WOLFHOUND */

#ifdef USE_NAMESPACE_WOLFHOUND
#define intlog wh_intlog
#define intpow wh_intpow
#define hash_simple wh_hash_simple
#endif /* USE_NAMESPACE_WOLFHOUND */

#endif /* _wh_header_maths_core_ */

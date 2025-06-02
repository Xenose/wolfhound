#ifndef _wh_header_maths_core_
#define _wh_header_maths_core_

#include<wh/common.h>
#include<wh/params/math.h>

extern i64 _wh_intlog(_wh_intlog_params params);
extern i64 _wh_intpow(_wh_intpow_params params);
extern i64 _wh_hash_simple(_wh_hash_simple_params params);

#define wh_intlog(...) _wh_intlog((_wh_intlog_params){ __VA_ARGS__ })
#define wh_intpow(...) _wh_intpow((_wh_intpow_params){ __VA_ARGS__ })

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

#endif /* _wh_header_maths_core_ */

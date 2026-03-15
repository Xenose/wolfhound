#ifndef _wh_header_maths_hash_
#define _wh_header_maths_hash_

#include<wh-common/common.h>
#include<wh/params/hash.h>

WH_C()

extern u32 _wh_hash_xx32(_wh_hash_xx32_params params);

#if !defined(__cplusplus) || !defined(WH_USE_C_MACRO_FUNC)

/* [MD_DOC]
 *
 * This is a custom implementation of the xxHash32 hashing function for
 * more details see (XXH32 Algorithm)[https://github.com/Cyan4973/xxHash/blob/release/doc/xxhash_spec.md].
 *
 * @d_param(const wh_buffer_s*) buffer : The buffer with the data, the buffer must be aligned in memory or it might crash.
 * @d_opt(u32) seed : A seed to be added to the steps of the hashing function.
 *
 * ## Return
 * This function returns a unsigned 32 bit integer that is the hash value.
 */
#define wh_hash_xx32(...) WH_EPF(_wh_hash_xx32((_wh_hash_xx32_params){__VA_ARGS__}))

#endif /* !defined(__cplusplus) || !defined(WH_USE_C_MACRO_FUNC) */

WH_C_END()

#endif /* _wh_header_maths_hash_ */

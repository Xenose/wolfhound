#ifndef _wh_header_maths_hash_
#define _wh_header_maths_hash_

#include<wh-common/common.h>
#include<wh/params/hash.h>

WH_C()

extern u32 _wh_hash_xx32(_wh_hash_xx32_params params);

#if !defined(__cplusplus) || !defined(WH_USE_C_MACRO_FUNC)

#define wh_hash_xx32(...) WH_EPF(_wh_hash_xx32((_wh_hash_xx32_params){__VA_ARGS__}))

#endif /* !defined(__cplusplus) || !defined(WH_USE_C_MACRO_FUNC) */

WH_C_END()

#endif /* _wh_header_maths_hash_ */

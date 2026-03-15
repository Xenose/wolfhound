#ifndef _wh_header_maths_hash_
#define _wh_header_maths_hash_

#include<wh-common/common.h>

typedef struct {
	wh_buffer_s buffer;
	u32 seed;
} _wh_hash_xx32_params;

extern u32 _wh_hash_xx32(_wh_hash_xx32_params params);


#define wh_hash_xx32(...) WH_EPF(_wh_hash_xx32((_wh_hash_xx32_params){__VA_ARGS__}))

#endif /* _wh_header_maths_hash_ */

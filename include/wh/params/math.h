#ifndef _wh_header_params_math_
#define _wh_header_params_math_

#include<wh-common/common.h>

typedef struct {
	i64 value;
	i64 base;
} _wh_intpos_params;

typedef struct {
	u64 value;
	u64 base;
} _wh_uintpos_params;

typedef struct {
	i64 times;
	i64 value;
} _wh_intpow_params;

typedef struct {
	const char* str;
	i64 limit;
	u64 length;
} _wh_hash_simple_params;

#endif /* _wh_header_params_math_ */

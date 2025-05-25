#ifndef _wh_header_params_math_
#define _wh_header_params_math_

#include<wh/common.h>

typedef struct {
	i64 value;
	i64 base;
} _wh_intlog_params;

typedef struct {
	i64 times;
	i64 value;
} _wh_intpow_params;

typedef struct {
	const char* str;
	u64 limit;
	u64 length;
} _wh_hash_simple_params;

#endif /* _wh_header_params_math_ */

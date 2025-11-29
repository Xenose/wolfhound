#ifndef _wh_header_convert_
#define _wh_header_convert_

#include<wh/common.h>

typedef struct {
	u64 value;
	char* buffer;
	u64 buffer_length;
	u64 base;
} _wh_uint2str_params;

typedef struct {
	i64 value;
	char* buffer;
	u64 buffer_length;
	u64 base;
} _wh_int2str_params;

typedef struct {
	char* buffer;
	i64 buffer_length;
	i64 base;
	i64* value_length;
} _wh_str2int_params;

typedef struct {
	char* buffer;
	int64_t buffer_length;
} _wh_strint_pull_params;

typedef struct {
	char* buffer;
	u64 length;
} _wh_str_invert_params;

typedef struct {
	i64 type_id;
} _wh_filetype2str_params;

extern char* _wh_uint2str(_wh_uint2str_params params);
extern char* _wh_int2str(_wh_int2str_params params);
extern i64 _wh_str2int(_wh_str2int_params params);
extern void _wh_str_invert(_wh_str_invert_params params);
extern const char* _wh_filetype2str(_wh_filetype2str_params params);

#define wh_uint2str(...) WH_EPF(_wh_uint2str((_wh_uint2str_params) { __VA_ARGS__ }))
#define wh_int2str(...) WH_EPF(_wh_int2str((_wh_int2str_params) { __VA_ARGS__ }))
#define wh_str2int(...) WH_EPF(_wh_str2int((_wh_str2int_params) { __VA_ARGS__ }))
#define wh_str_invert(...) WH_EPF(_wh_str_invert((_wh_str_invert_params) { __VA_ARGS__ }))
#define wh_filetype2str(...) WH_EPF(_wh_filetype2str((_wh_filetype2str_params) { __VA_ARGS__ }))

#ifdef USE_NAMESPACE_WOLFHOUND
#define uint2str wh_uint2str
#define int2str wh_int2str
#define str2int wh_str2int
#define str_invert wh_str_invert
#endif

#endif /* _wh_header_convert_ */

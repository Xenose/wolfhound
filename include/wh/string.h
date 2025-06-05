#ifndef _wh_header_string_
#define _wh_header_string_

#include<wh/common.h>
#include<wh/params/string.h>

extern wh_string_s _wh_string_append(_wh_string_append_params, ...);
extern wh_string_s _wh_string_create(int dummy, ...);
extern const char* _wh_strstr(_wh_strstr_params params);

#define wh_string_append(x, ...)		_wh_string_append((_wh_string_append_params) { WH_VA_ARGS x }, __VA_OPT__(, __VA_ARGS__ ))
#define wh_string_create(...)			_wh_string_create(0, __VA_ARGS__, nullptr)
#define wh_strstr(...)					_wh_strstr((_wh_strstr_params) { __VA_ARGS__ })

#endif /* _wh_header_string_ */

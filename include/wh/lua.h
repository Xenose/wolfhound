#ifndef _wh_header_lua_
#define _wh_header_lua_

// my libs
#include<wh/common.h>

typedef struct {
	lua_State* lstate;
	i64 number;
} _wh_lua_addint_params;

#define wh_lua_addint(x, ...) _wh_lua_addint((_wh_lua_addint_params) { WH_VA_ARGS x }, __VA_ARGS__, nullptr))
#endif /* _wh_header_lua_ */

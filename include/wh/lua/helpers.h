#ifndef _wh_header_lua_helpers_
#define _wh_header_lua_helpers_

#include<wh-headers/lua.h>
#include<wh/common.h>

extern i8 _wh_lua_add_values(lua_State* ls, ...);
extern i8 _wh_lua_get_values(lua_State* ls, ...);
extern u8 _wh_lua_get_flag(lua_State* ls, unsigned flag, ...);

#define wh_lua_add_values(ls, ...)		WH_EPF(_wh_lua_add_values(ls, __VA_ARGS__, nullptr))
#define wh_lua_get_values(ls, ...)		WH_EPF(_wh_lua_get_values(ls, __VA_ARGS__, nullptr))

#define wh_lua_get_flag(ls, flag, ...)	WH_EPF((!!_wh_lua_get_flag(ls, flag, __VA_ARGS__, nullptr)))

#endif /* _wh_header_lua_helpers_ */

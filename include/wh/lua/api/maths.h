#ifndef _wh_header_lua_api_maths_
#define _wh_header_lua_api_maths_

#include<wh-core/common.h>
#include<wh/headers/lua.h>

WH_C()

extern int wh_lua_intpos(lua_State* ls);
extern int wh_lua_intpow(lua_State* ls);
extern int wh_lua_hash_simple(lua_State* ls);

WH_C_END()

#endif /* _wh_header_lua_api_maths_ */

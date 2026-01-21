#ifndef _wh_headers_lua_
#define _wh_headers_lua_

#include<wh-common/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_FREEBSD)
	// TODO remove hard coding of lua path in cmake
	#include<lua54/lua.h>
	#include<lua54/lualib.h>
	#include<lua54/lauxlib.h>
#else
	#include<lua.h>
	#include<lualib.h>
	#include<lauxlib.h>
#endif

// Older versions don't have "is integer"
#if LUA_VERSION_NUM < 503
	static int lua_isinteger(lua_State *L, int idx) {
		if (!lua_isnumber(L, idx)) return 0;
		lua_Number n = lua_tonumber(L, idx);
		lua_Integer i = (lua_Integer)n;
		return n == (lua_Number)i;
	}
#endif

#ifndef LUA_OK
	#define LUA_OK 0
#endif

WH_C_END()

#endif

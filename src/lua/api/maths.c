#include<lualib.h>
#include<lauxlib.h>

#include<wh/maths/core.h>
#include<wh/lua/api/maths.h>


int wh_lua_intlog(lua_State* ls) {
	int argc = 0;
	int out = 0;
	int value = 0;
	int base = 0;

	argc = lua_gettop(ls);
	value = luaL_checkinteger(ls, 1);
	base = luaL_checkinteger(ls, 2);

	out = wh_intlog(value, base);

	lua_pushinteger(ls, out);
	return 1;
}

int wh_lua_intpow(lua_State* ls) {
	int argc = 0;
	int out = 0;
	int value = 0;
	int base = 0;

	argc = lua_gettop(ls);
	value = luaL_checkinteger(ls, 1);
	base = luaL_checkinteger(ls, 2);

	out = wh_intpow(value, base);

	lua_pushinteger(ls, out);
	return 1;
}

int wh_lua_hash_simple(lua_State* ls) {
	int argc = 0;
	const char* str = nullptr;
	i64 limit = 0;

	argc = lua_gettop(ls);
	str = luaL_checkstring(ls, 1);
	limit = luaL_checkinteger(ls, 2);

	lua_pushinteger(ls, wh_hash_simple(str, limit));
	return 1;
}

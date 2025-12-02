#include<lualib.h>
#include<lauxlib.h>

#include<wh-sys/file.h>
#include<wh/lua/api/file.h>

int wh_lua_file_read(lua_State* ls) {
	int argc = 0;
	const char* path = nullptr;
	wh_file_s file = { 0 };

	argc = lua_gettop(ls);
	path = luaL_checkstring(ls, 1);
	file = wh_file_load(path);

	lua_pushstring(ls, file.str);
	wh_file_unload(file);
	return 1;
}

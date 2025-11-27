#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<stdarg.h>

#include<wh/lua/functions.h>
#include<wh/lua/file.h>

i8 _wh_lua_functions(lua_State* ls, const char* table, int index, ...) {
	va_list args;
	const char* name = nullptr;

	va_start(args, index);
	lua_newtable(ls);

	while (nullptr != (name = va_arg(args,const char*))) {
		lua_pushcfunction(ls, va_arg(args, int (*)(lua_State)));
		lua_setfield(ls, index, name);
	}

	lua_setfield(ls, -2, table);
	va_end(args);
	return 0;
}

i8 _wh_lua_load_api() {
	lua_State* ls;

	// Create a new table
	lua_newtable(ls); // CONFIG

	_wh_lua_functions(
		ls, "file", -2,
		"load", wh_lua_file_load,
		nullptr
	);

	lua_setglobal(ls, "WH");
	return 0;
}

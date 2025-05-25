#include<stdarg.h>
#include<wh/lua.h>

i8 _wh_lua_addint(_wh_lua_addint_params params, ...) {
	char* str;
	va_list args;
	va_start(args, params);

	while (nullptr != (str = va_arg(args, char*))) {
	}

	lua_pushnumber(params.lstate, params.number);

	return 0;
}

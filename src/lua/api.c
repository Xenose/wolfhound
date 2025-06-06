#include<wh/lua/api.h>
#include<wh/lua/helpers.h>

#include<wh/lua/api/file.h>
#include<wh/lua/api/filesystem.h>
#include<wh/lua/api/maths.h>

i8 _wh_lua_expose_api(lua_State* ls) {
	wh_lua_add_values(
		ls,
		(const char*[]){ "WH", "file", "read",					nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_file_read,
		(const char*[]){ "WH", "file", "dir", "read",		nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_dir_read,
		(const char*[]){ "WH", "file", "dir", "close",		nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_dir_close,
		(const char*[]){ "WH", "maths", "int", "log",		nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_intlog,
		(const char*[]){ "WH", "maths", "int", "pow",		nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_intpow,
		(const char*[]){ "WH", "maths", "hash", "simple",	nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_hash_simple
	);
	return 0;
}

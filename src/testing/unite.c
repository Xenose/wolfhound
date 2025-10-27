#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<wh/print.h>
#include<wh/debug/logger.h>
#include<wh/lua/api.h>
#include<wh/sys/filesystem.h>
#include<wh/memory.h>
#include<wh/testing/unite.h>
#include<wh/file.h>
#include<wh/string.h>

i8 _wh_run_utests(const char* path) {
	wh_file_s file = { 0 };
	lua_State* ls = nullptr;
	char p[1024] = { 0 };
	wh_dir_s dir = wh_read_dir(nullptr, path);

	ls = luaL_newstate();
	_wh_lua_expose_api(ls);

	wh_for(i64, i, dir.count) {
		wh_strcat((p, 1024), path, "/", dir.entries[i].name);
		wh_print(("RUNNING UNITE TEST [ %s ]\n"), p);

		file = wh_file_load(p);

		// Here we load the string and use lua_pcall for run the code
		if (LUA_OK == luaL_loadstring(ls, file.str)) {
			if (LUA_OK == lua_pcall(ls, 0, 0, 0)) {
				// If it was executed successfully we 
				// remove the code from the stack
				lua_pop(ls, lua_gettop(ls));
			} else {
				const char *error_msg = lua_tostring(ls, -1);
				wh_log_error(("Failed to pop [ %s ] -> [ %s ]"), p, error_msg);
				lua_pop(ls, 1); // remove error message from stack
			}
		} else wh_log_error(("Failed to launch [ %s ]"), p);

		wh_file_unload(file);
	}

	wh_dir_destroy(nullptr, &dir);
	lua_close(ls);
	return 0;
}

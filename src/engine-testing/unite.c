#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<wh-sys/file.h>
#include<wh-sys/filesystem.h>
#include<wh-testing/unite.h>
#include<wh/debug/logger.h>
#include<wh/lua/api.h>
#include<wh/memory.h>
#include<wh/print.h>
#include<wh/string.h>

ai64 count_failed;
ai64 count_passed;

i8 _wh_run_utests(const char* path) {
	wh_file_s file = { 0 };
	lua_State* ls = nullptr;
	char p[1024] = { 0 };
	wh_dir_s dir = wh_read_dir(nullptr, path);

	ls = luaL_newstate();
	_wh_lua_expose_api(ls);

	wh_for(u64, i, dir.count) {
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

void _wh_test(int result, const char* result_str) {
	if (result) {
		++(count_failed);
		printf("\t[\033[31mFAILED\033[0m] %s for [ \033[33m%s\033[0m ]\n", result_str, result_str);\
	} else {
		++(count_passed);
		printf("[\033[32mPASSED\033[0m] %s for [ \033[33m%s\033[0m ]\n", result_str, result_str); \
	}
}

#include<wh/sys/filesystem.h>
#include<wh/file.h>
#include<wh/loader/asset.h>
#include<wh/print.h>
#include<wh/debug/logger.h>

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<string.h>

typedef struct {
	wh_string_s name;
} wh_asset_s;

i64 _wh_assets_load_inner(lua_State* ls, const char* path) {
	wh_file_s file = { 0 };
	char p[1024] = { 0 };
	wh_dir_s dir = wh_read_dir(nullptr, path);

	wh_for(i64, i, dir.count) {
		wh_print(("%s\n"), dir.entries[i].name);

		switch(dir.entries[i].type) {
			case WH_FSYS_DIR:
				memcpy(p, path, strlen(path));
				strcat(p, "/");
				strcat(p, dir.entries[i].name);

				_wh_assets_load(p);
				break;
			case WH_FSYS_FILE:

				memcpy(p, path, strlen(path));
				strcat(p, "/");
				strcat(p, dir.entries[i].name);
				
				wh_log_debug(("Loading asset [ %s ]"), p);
				file = wh_file_load(p);

				if (0 == file.length) {
					wh_log_warning(("No file fund at [ %s ]"), path);
					continue;
				}

				// Here we load the string and use lua_pcall for run the code
				if (LUA_OK == luaL_loadstring(ls, file.str)) {
					if (LUA_OK == lua_pcall(ls, 0, 0, 0)) {
						// If it was executed successfully we 
						// remove the code from the stack
						lua_pop(ls, lua_gettop(ls));
					}
				}

				wh_file_unload(file);
				break;
		}
	}

go_error_exit:
	wh_dir_destroy(nullptr, &dir);
	return 0;
}
i64 _wh_assets_load(const char* path) {
	lua_State* ls = luaL_newstate();
	luaL_openlibs(ls);

	_wh_assets_load_inner(ls, path);

	lua_close(ls);
	return 0;
}

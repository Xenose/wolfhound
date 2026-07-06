#include<wh-sys/file.h>
#include<wh/loader/asset.h>
#include<wh/print.h>
#include<wh/debug/logger.h>
#include<wh/lua/helpers.h>
#include<wh/lua/api.h>
#include<wh/string.h>

#include<wh-headers/lua.h>

#include<wh-posix/errno.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/string.h>
#include<wh-posix/dirent.h>
#include<wh-posix/sys/stat.h>


#include<wh-sys/filesystem.h>

typedef struct {
	struct_type stype;
	wh_string_s name;
} wh_asset_s;

i64 _wh_assets_load_inner(lua_State* ls, const char* path) {
	wh_file_s file = { 0 };
	char p[1024] = { 0 };
	wh_dir_s dir = wh_read_dir(nullptr, path);

	wh_for(u64, i, dir.count) {
		wh_asset_s asset = { 0 };
		wh_log_debug(("Loading asset: %s"), dir.entries[i].name);

		switch(dir.entries[i].type) {
			case WH_FSYS_DIR:
				wh_strcat((p, 1023), path, "/", dir.entries[i].name);
				_wh_assets_load(p);
				break;
			case WH_FSYS_FILE:
				wh_strcat((p, 1024), path, "/", dir.entries[i].name);

				wh_log_debug(("Loading asset [ %s ]"), p);
				file = wh_file_load(p);

				if (0 == file.length) {
					wh_log_warning(("No file fund at [ %s ]"), path);
					continue;
				}

				wh_lua_add_values(
					ls,
					(const char*[]) { "WH", "asset", "type", nullptr }, WH_TYPE_I64, asset.stype
				);

				// Here we load the string and use lua_pcall for run the code
				if (LUA_OK == luaL_loadstring(ls, file.str)) {
					if (LUA_OK == lua_pcall(ls, 0, 0, 0)) {
						// If it was executed successfully we 
						// remove the code from the stack
						lua_pop(ls, lua_gettop(ls));
					}
				}

				wh_lua_get_values(
					ls,
					(const char*[]) { "WH", "asset", "type", nullptr }, WH_TYPE_I64, &asset.stype
				);

				wh_log_debug(("Asset type set to $F"), asset.stype);

				wh_file_unload(file);
				break;
		}
	}

go_error_exit:
	wh_dir_destroy(nullptr, &dir);
	return 0;
}

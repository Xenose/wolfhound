#include<wh-sys/file.h>
#include<wh/loader/asset.h>
#include<wh/print.h>
#include<wh/debug/logger.h>
#include<wh/lua/helpers.h>
#include<wh/lua/api.h>
#include<wh/string.h>

#include<wh-posix/string.h>
#include<wh-headers/lua.h>
#include<wh-posix/dirent.h>

#include<wh-sys/filesystem.h>

typedef struct {
	struct_type stype;
	wh_string_s name;
} wh_asset_s;

/* i64 _wh_assets_load_inner(lua_State* ls, const char* path) {
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
} */


i64 _wh_assets_load_inner(lua_State* ls, const char* path) {
	i64 rc = 0;
	DIR* dir = nullptr;
	char _path[256] = { 0 };
	u64 _path_length = 0;

	if (nullptr == path) {
		goto go_error_exit;
	}

	if (nullptr == (dir = opendir(path))) {
		wh_log_error(("Failed to load asset path: %s"), path);
		goto go_error_exit;
	}

	_path_length = strlen(path);

	for (struct dirent* entry = readdir(dir); nullptr != entry; entry = readdir(dir)) {
		if (!strcmp("..", entry->d_name)) {
			continue;
		}

		if (!strcmp(".", entry->d_name)) {
			continue;
		}

		memcpy(_path, path, _path_length);
		wh_strcat((_path, 255, _path_length), "/", entry->d_name);
		wh_log_debug(("Name: %s"), _path);

	}

	closedir(dir);
go_error_exit:
	return 0;
}

i64 _wh_assets_load(const char* path) {
	lua_State* ls = luaL_newstate();

	wh_log_debug(("Loading game assets Lua state"));
	_wh_lua_expose_api(ls);
	_wh_assets_load_inner(ls, path);

	lua_close(ls);
	return 0;
}

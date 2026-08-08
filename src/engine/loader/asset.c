#include<wh-sys/file.h>
#include<wh/loader/asset.h>
#include<wh/print.h>
#include<wh/debug/logger.h>
#include<wh/lua/helpers.h>
#include<wh/lua/api.h>
#include<wh/string.h>

#include<wh/headers/lua.h>

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
	i64 rc = 0;
	DIR* dir = nullptr;
	char _path[256] = { 0 };
	u64 _path_length = 0;
	struct stat st = { 0 };

	if (nullptr == path) {
		wh_log_warning(("Provided asset path is NULL!"));
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

		if (0 != lstat(_path, &st)) {
			wh_log_error(("Failed to read stats for [ $n ]"), errno);
			memset(_path, 0, 256);
			continue;
		}

		if (st.st_mode & S_IFDIR) {
				wh_log_debug(("Found a dir [ %s ]!"), _path);
				_wh_assets_load_inner(ls, _path);
		} else if (st.st_mode & S_IFREG) {
				wh_log_debug(("Found a file!"));
				wh_file_s file = wh_file_load(_path);
				// TODO
				// Here once we have a gameobject format defined
				// we will use lua to populate it and define the
				// data blocks

				if (nullptr != file.ptr) {
					if (LUA_OK != luaL_dostring(ls, file.str)) {
						const char *error_msg = lua_tostring(ls, -1);
						wh_log_warning(("Lua error: %s"), error_msg);
						lua_pop(ls, 1); // remove error message from stack
					}

					wh_file_unload(file);
				}
		}

		memset(_path, 0, 256);
	}

go_error_close_dir_exit:
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

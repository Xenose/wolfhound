#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<string.h>

#include<wh/print.h>
#include<wh/arg_parser.h>
#include<wh/maths/core.h>
#include<wh/debug/logger.h>
#include<wh/file.h>
#include<wh/lua/config.h>
#include<wh/string.h>
#include<wh/lua/helpers.h>

i64 _wh_args_parse(_wh_args_parse_params params) {
	char command[256] = { 0 };
	wh_config_s* config = params.config;

	for (i64 i = 1; i < params.arc; i++) {
		char* const* start = &params.arv[i];
		char* in = params.arv[i];
		u64 length = strlen(in);

		if (1 >= length) {
			continue;
		}

		if ('-' == in[0]) {
			if ('-' == in[1]) {
				wh_strcat((command, 255), "commands/", &in[2], ".lua");
				wh_log_debug(("calling command [ %s ]"), command);

				wh_file_s file = wh_file_load(command);

				for (i++; i < params.arc; i++) {
					if ('-' == params.arv[i][0]) {
						i--;
						break;
					}

					wh_lua_add_values(params.ls, (const char*[]) { "args", nullptr }, WH_TYPE_ARRAY_STRING, &params.arv[i] - start - 1, &start[1]);
				}

				if (nullptr != file.ptr) {
					if (LUA_OK != luaL_dostring(params.ls, file.str)) {
						const char *error_msg = lua_tostring(params.ls, -1);
						wh_log_warning(("Lua error: %s"), error_msg);
						lua_pop(params.ls, 1); // remove error message from stack
					}

					wh_file_unload(file);
				}
			} else {
			}
		}
	}

	return 0;
}

i64 _wh_args_parser_init(void) {
	return 0;
}

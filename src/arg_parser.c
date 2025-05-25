#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<string.h>

#include<wh/print.h>
#include<wh/arg_parser.h>
#include<wh/maths.h>
#include<wh/debug.h>
#include<wh/file.h>
#include<wh/lua/config.h>


i64 _wh_args_parse(_wh_args_parse_params params) {
	char command[256] = { 0 };
	wh_config_s* config = params.config;


	for (i64 i = 1; i < params.arc; i++) {
		char* in = params.arv[i];
		u64 length = strlen(in);

		if ('-' == params.arv[i][0]) {
			if ('-' == params.arv[i][1]) {
				memcpy(command, "commands/", 9);
				strcat(command, &in[2]);
				strcat(command, ".lua");

				wh_log_debug(("calling command [ %s ]"), command);

				wh_file_s file = wh_file_load(command);
				memset(command, 0, 256);

				if (nullptr != file.ptr) {
					if (LUA_OK != luaL_dostring(params.ls, file.str)) {
						const char *error_msg = lua_tostring(params.ls, -1);
						wh_log_debug(("Lua error: %s"), error_msg);
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

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#include<stdarg.h>

#include<wh/file.h>
#include<wh/debug/logger.h>
#include<wh/config.h>
#include<wh/arg_parser.h>
#include<wh/lua/config.h>
#include<wh/lua/helpers.h>
#include<wh/lua/api.h>

i8 _wh_conf_defaults(_wh_init_params* params, wh_config_s* config) {
	config->heap.size = 4096 < params->heap_size ? params->heap_size : WH_64MB;
	return 0;
}

static void _config_lua(_wh_init_params* params, wh_config_s* conf, lua_State* ls) {
	wh_file_s cf = { 0 };
	u64 heap_size = 0;

	wh_log_debug(("Reading config from [ %s ]"), params->config_path.str);
	cf = wh_file_load(params->config_path.ptr);

	if (0 == cf.length) {
		wh_log_warning(("No file fund at [ %s ]"), params->config_path.str);
		goto go_skip_lua;
	}

	 // Here we load the string and use lua_pcall for run the code
	if (LUA_OK == luaL_loadstring(ls, cf.str)) {
		if (LUA_OK == lua_pcall(ls, 0, 0, 0)) {
			// If it was executed successfully we 
			// remove the code from the stack
			lua_pop(ls, lua_gettop(ls));
		}
	}

	go_skip_lua:
	return;
}

wh_config_s _wh_config_load(_wh_init_params* params, wh_config_s* config) {
	lua_State* ls = nullptr;

	wh_log_debug(("Starting new lua_State"));
	ls = luaL_newstate();
	luaL_openlibs(ls);
	_wh_lua_expose_api(ls);

	// Variable loading
	//wh_config_lua_expose(ls, conf);
	wh_lua_add_values(
		ls,
		(const char*[]) { "WH", "config", "heap", "size", nullptr }, WH_TYPE_I64, config->heap.size,

		(const char*[]) { "WH", "config", "flags", "dryrun", nullptr },			WH_TYPE_BOOL, config->flags.dryrun,
		(const char*[]) { "WH", "config", "flags", "run_tests", nullptr },		WH_TYPE_BOOL, config->flags.run_tests,
		(const char*[]) { "WH", "config", "flags", "log_debug", nullptr},			WH_TYPE_BOOL, config->flags.log_debug,
		(const char*[]) { "WH", "config", "flags", "log_info", nullptr},			WH_TYPE_BOOL, config->flags.log_info,
		(const char*[]) { "WH", "config", "flags", "log_notice", nullptr},		WH_TYPE_BOOL, config->flags.log_notice,
		(const char*[]) { "WH", "config", "flags", "log_warning", nullptr},		WH_TYPE_BOOL, config->flags.log_warning,
		(const char*[]) { "WH", "config", "flags", "log_error", nullptr},			WH_TYPE_BOOL, config->flags.log_error,
		(const char*[]) { "WH", "config", "flags", "log_critical", nullptr},		WH_TYPE_BOOL, config->flags.log_critical,
		(const char*[]) { "WH", "config", "flags", "log_alert", nullptr},			WH_TYPE_BOOL, config->flags.log_alert,
		(const char*[]) { "WH", "config", "flags", "log_emergency", nullptr},	WH_TYPE_BOOL, config->flags.log_emergency
	);

	_wh_args_parser_init();
	_wh_conf_defaults(params, config);
	_config_lua(params, config, ls);
	wh_args_parse(ls, params->args.count, params->args.ptr, config);

	wh_lua_get_values(
		ls,
		(const char*[]) { "WH", "config", "heap", "size", nullptr }, WH_TYPE_I64, &config->heap.size
	);

	// Testing
	config->flags.dryrun = wh_lua_get_flag(
		ls, config->flags.dryrun, (const char*[]) { "WH", "config", "flags", "dryrun", nullptr });
	config->flags.run_tests = wh_lua_get_flag(
		ls, config->flags.run_tests, (const char*[]) { "WH", "config", "flags", "run_tests", nullptr });

	// Logging flags
	config->flags.log_debug = wh_lua_get_flag(
		ls, config->flags.log_debug, (const char*[]) { "WH", "config", "flags", "log_debug", nullptr });
	config->flags.log_info = wh_lua_get_flag(
		ls, config->flags.log_info, (const char*[]) { "WH", "config", "flags", "log_info", nullptr });
	config->flags.log_notice = wh_lua_get_flag(
		ls, config->flags.log_notice, (const char*[]) { "WH", "config", "flags", "log_notice", nullptr });
	config->flags.log_warning = wh_lua_get_flag(
		ls, config->flags.log_warning, (const char*[]) { "WH", "config", "flags", "log_warning", nullptr });
	config->flags.log_error = wh_lua_get_flag(
		ls, config->flags.log_error, (const char*[]) { "WH", "config", "flags", "log_error", nullptr });
	config->flags.log_critical = wh_lua_get_flag(
		ls, config->flags.log_critical, (const char*[]) { "WH", "config", "flags", "log_critical", nullptr });
	config->flags.log_alert = wh_lua_get_flag(
		ls, config->flags.log_alert, (const char*[]) { "WH", "config", "flags", "log_alert", nullptr });
	config->flags.log_emergency = wh_lua_get_flag(
		ls, config->flags.log_emergency, (const char*[]) { "WH", "config", "flags", "log_emergency", nullptr });

	wh_log_set_level(WH_LOG_LEVEL_DEBUG,		config->flags.log_debug);
	wh_log_set_level(WH_LOG_LEVEL_INFO,			config->flags.log_info);
	wh_log_set_level(WH_LOG_LEVEL_NOTICE,		config->flags.log_notice);
	wh_log_set_level(WH_LOG_LEVEL_WARNING,		config->flags.log_warning);
	wh_log_set_level(WH_LOG_LEVEL_ERROR,		config->flags.log_error);
	wh_log_set_level(WH_LOG_LEVEL_CRITICAL,	config->flags.log_critical);
	wh_log_set_level(WH_LOG_LEVEL_ALERT,		config->flags.log_alert);
	wh_log_set_level(WH_LOG_LEVEL_EMERGENCY,	config->flags.log_emergency);

	lua_close(ls);
	return *config;
}

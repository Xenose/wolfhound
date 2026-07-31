#include<stdarg.h>

#include<wh-headers/lua.h>
#include<wh/lua/config.h>
#include<wh/lua/helpers.h>

i8 _wh_lua_add_ints(_wh_lua_add_ints_params params, ...) {
    va_list args;
    const char* name = nullptr;

    va_start(args, params);
    lua_newtable(params.ls);

    while (nullptr != (name = va_arg(args,const char*))) {
        lua_pushinteger(params.ls, va_arg(args, i64));
        lua_setfield(params.ls, params.index, name);
    }

    lua_setfield(params.ls, params.index, params.table);
    va_end(args);
    return 0;
}

i8 _wh_lua_add_uints(_wh_lua_add_uints_params params, ...) {
    va_list args;
    const char* name = nullptr;

    va_start(args, params);
    lua_newtable(params.ls);

    while (nullptr != (name = va_arg(args,const char*))) {
        lua_pushinteger(params.ls, va_arg(args, u64));
        lua_setfield(params.ls, params.index, name);
    }

    lua_setfield(params.ls, params.index, params.table);
    va_end(args);
    return 0;
}

i8 _wh_lua_read_uints(_wh_lua_add_uints_params params, ...) {
    va_list args;
    const char* name = nullptr;

    va_start(args, params);

    lua_getglobal(params.ls, "WH");

    if (!lua_istable(params.ls, -1)) {
        goto go_error_exit;
    }

    lua_getfield(params.ls, -1, params.table);

    if (lua_istable(params.ls, -1)) {
    }

    while (nullptr != (name = va_arg(args,const char*))) {
        lua_getfield(params.ls, params.index, name);

        //if (lua_isinteger(ls, -1)) {
        //	*data = lua_tointeger(ls, -1);
        //}
        //lua_pushinteger(params.ls, va_arg(args, u64));
        //lua_setfield(params.ls, params.index, name);
    }

go_error_exit:
    va_end(args);
    return 0;
}

i8 _wh_lua_add_bools(_wh_lua_add_bools_params params, ...) {
    va_list args;
    const char* name = nullptr;

    va_start(args, params);
    lua_newtable(params.ls);

    while (nullptr != (name = va_arg(args,const char*))) {
        lua_pushboolean(params.ls, va_arg(args, int));
        lua_setfield(params.ls, params.index, name);
    }

    lua_setfield(params.ls, params.index, params.table);
    va_end(args);
    return 0;
}

i8 _wh_config_lua_expose(_wh_config_lua_expose_params params) {
    lua_State* ls = params.ls;
    wh_config_s* config = params.config;

    /*
    // Create a new table
    lua_newtable(ls); // CONFIG

    wh_lua_add_bools(
    (ls, "flags", -2),
    "dryrun",			config->flags.dryrun,

    // log flags
    "log_debug",		config->flags.log_debug,
    "log_info",			config->flags.log_info,
    "log_notice",		config->flags.log_notice,
    "log_warning",		config->flags.log_warning,
    "log_error",		config->flags.log_error,
    "log_critical",	config->flags.log_critical,
    "log_alert",		config->flags.log_alert,
    "log_emergency",	config->flags.log_emergency
    );
    */

    wh_lua_add_values(
            ls,
            (const char*[]) { "TEST", nullptr }, WH_TYPE_I64, 42,

            (const char*[]) { "WH", "config", "flags", "dryrun", nullptr },			WH_TYPE_BOOL, config->flags.dryrun,
            (const char*[]) { "WH", "config", "flags", "log_debug", nullptr},			WH_TYPE_BOOL, config->flags.log_debug,
            (const char*[]) { "WH", "config", "flags", "log_info", nullptr},			WH_TYPE_BOOL, config->flags.log_info,
            (const char*[]) { "WH", "config", "flags", "log_notice", nullptr},		WH_TYPE_BOOL, config->flags.log_notice,
            (const char*[]) { "WH", "config", "flags", "log_warning", nullptr},		WH_TYPE_BOOL, config->flags.log_warning,
            (const char*[]) { "WH", "config", "flags", "log_error", nullptr},			WH_TYPE_BOOL, config->flags.log_error,
            (const char*[]) { "WH", "config", "flags", "log_critical", nullptr},		WH_TYPE_BOOL, config->flags.log_critical,
            (const char*[]) { "WH", "config", "flags", "log_alert", nullptr},			WH_TYPE_BOOL, config->flags.log_alert,
            (const char*[]) { "WH", "config", "flags", "log_emergency", nullptr},	WH_TYPE_BOOL, config->flags.log_emergency
            );



    /*
       wh_lua_add_uints(
       (ls, "heap", -2),

       "size", config->heap.size
       );

       lua_setglobal(ls, "CONFIG");*/
    return 0;
}

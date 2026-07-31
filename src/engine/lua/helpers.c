#include<stdarg.h>

#include<wh-headers/lua.h>
#include<wh/debug/logger.h>
#include<wh/print.h>
#include<wh/lua/helpers.h>

i64 _wh_lua_add_keys(lua_State* ls, const char** keys, i64 index) {
    lua_getglobal(ls, keys[0]);

    if (lua_isnil(ls, -1)) {
        lua_pop(ls, 1);
        lua_newtable(ls);
        lua_pushvalue(ls, -1);
        lua_setglobal(ls, keys[0]);
    }

    for (;nullptr != keys[index + 1]; index++) {
        lua_getfield(ls, -1, keys[index]);

        if (lua_isnil(ls, -1)) {
            lua_pop(ls, 1);
            lua_newtable(ls);
            lua_pushvalue(ls, -1);
            lua_setfield(ls, -3, keys[index]);
        }

        lua_remove(ls, -2);
    }

    return index;
}

// ( [ "namespace", "table", "table", ..., "var_name", nullptr ], type, value )
i8 _wh_lua_add_values(lua_State* ls, ...) {
    va_list args;
    void* array;
    i64 array_length = 0;
    const char** keys = nullptr;

    va_start(args, ls);

    while (nullptr != (keys = va_arg(args, const char**))) {
        i64 i = 1;
        i64 type = 0;

        if (nullptr == keys[0]) {
            wh_log_error(("Failed to add table, nullptr given"));
            goto go_error_exit;
        } else if (nullptr == keys[1]) {
            goto go_get_value;
        }

        i = _wh_lua_add_keys(ls, keys, i);

go_get_value:
        // We need to know what type we are getting.
        type = va_arg(args, int);

        // inserting the value
        switch (type) {
            case WH_TYPE_I64:
                lua_pushinteger(ls, va_arg(args, i64));
                break;
            case WH_TYPE_BOOL:
                lua_pushboolean(ls, va_arg(args, int));
                break;
            case WH_TYPE_STRING:
                lua_pushstring(ls, va_arg(args, char*));
                break;
            case WH_TYPE_ARRAY_STRING:
                array_length = va_arg(args, i64) + 1;
                array = va_arg(args, char**);

                lua_createtable(ls, (int)array_length, 0);

                for (i64 j = 0; j < array_length; j++) {
                    lua_pushstring(ls, ((char**)array)[j]);
                    lua_rawseti (ls, -2, j+1);
                }

                break;
            case WH_TYPE_FUNCTION_PTR:
                lua_pushcfunction(ls, (int(*)(lua_State*))va_arg(args, void*));
                break;
            default:
                wh_log_error(("Value of [ %d ] given to key [ %s ]"), type, keys[i]);
                goto go_error_exit;
        }

        if (nullptr == keys[1]) {
            lua_setglobal(ls, keys[0]);
        } else {
            lua_setfield(ls, -2, keys[i]);
            lua_pop(ls, 1);
        }
    }

    va_end(args);
    return 0;
go_error_exit:
    va_end(args);
    return -1;
}

i8 _wh_lua_get_values(lua_State* ls, ...) {
    va_list args;
    const char** keys = nullptr;

    va_start(args, ls);

    while (nullptr != (keys = va_arg(args, const char**))) {
        i64 i = 1;
        i64 type = 0;
        void* out = nullptr;

        if (nullptr == keys[0]) {
            continue;
        }

        lua_getglobal(ls, keys[0]);

        if (nullptr == keys[1]) {
            goto go_switch;
        }

        if (!lua_istable(ls, -1)) {
            lua_pop(ls, 1);
            va_arg(args, i64);
            va_arg(args, void*);
            continue;
        }


        for (;nullptr != keys[i + 1]; i++) {
            lua_getfield(ls, -1, keys[i]);

            if (!lua_istable(ls, -1)) {
                lua_pop(ls, 3);
                va_arg(args, i64);
                va_arg(args, void*);
                continue;
            }

            lua_remove(ls, -2);
        }

        // Now getting the final value on the lua stack
        lua_getfield(ls, -1, keys[i]);

go_switch:
        // Getting the pointer
        type = va_arg(args, i64);
        out = va_arg(args, void*);

        if (nullptr == out) {
            lua_pop(ls, 1);
            continue;
        }

        switch (type) {
            case WH_TYPE_I64:
                if (lua_isinteger(ls, -1)) {
                    *((i64*)out) = lua_tointeger(ls, -1);
                }
                break;
            case WH_TYPE_BOOL:
                if (lua_isboolean(ls, -1)) {
                    *((i8*)out) = (i8)lua_toboolean(ls, -1);
                }
                break;
            default:
                lua_pop(ls, 1);
                goto go_error_exit;
        }


        if (nullptr != keys[1]) {
            lua_pop(ls, 1);
        }

        lua_pop(ls, 1);
    }

    va_end(args);
    return 0;
go_error_exit:

    va_end(args);
    return -1;
}

u8 _wh_lua_get_flag(lua_State* ls, unsigned flag, ...) {
    va_list args;
    const char** keys = nullptr;

    va_start(args, flag);

    if (nullptr != (keys = va_arg(args, const char**))) {
        i64 i = 1;

        if (nullptr == keys[0]) {
            goto go_exit;
        }

        lua_getglobal(ls, keys[0]);

        if (nullptr == keys[1]) {
            goto go_value;
        }

        if (!lua_istable(ls, -1)) {
            lua_pop(ls, 1);
            goto go_exit;
        }


        for (;nullptr != keys[i + 1]; i++) {
            lua_getfield(ls, -1, keys[i]);

            if (!lua_istable(ls, -1)) {
                lua_pop(ls, 3);
                va_arg(args, void*);
                continue;
            }

            lua_remove(ls, -2);
        }

        // Now getting the final value on the lua stack
        lua_getfield(ls, -1, keys[i]);

go_value:
        if (lua_isboolean(ls, -1)) {
            flag = (u8)lua_toboolean(ls, -1);
        }

        if (nullptr != keys[1]) {
            lua_pop(ls, 1);
        }

        lua_pop(ls, 1);
    }

go_exit:
go_error_exit:
    va_end(args);
    return (u8)flag;
}

#include<wh-headers/lua.h>
#include<wh/lua/api.h>
#include<wh/lua/helpers.h>

#include<wh/lua/api/file.h>
#include<wh/lua/api/filesystem.h>
#include<wh/lua/api/maths.h>

static void _lua_open_libs(lua_State* ls) {
#if LUA_VERSION_NUM < 505
    luaopen_base(ls);             /* opens the basic library */
    luaopen_table(ls);            /* opens the table library */
    luaopen_io(ls);               /* opens the I/O library */
    luaopen_string(ls);           /* opens the string lib. */
    luaopen_math(ls);             /* opens the math lib. */
#else
    luaL_openlibs(ls);
#endif
}

i8 _wh_lua_expose_api(lua_State* ls) {
    // Looks like luaL_openlibs is deprecated,
    // this is a work around for it.
    _lua_open_libs(ls);

    wh_lua_add_values(
            ls,

            // enums
            (const char*[]){ "WH_STRUCT_TYPE_INSTANCE",			nullptr },					WH_TYPE_I64, WH_STRUCT_TYPE_INSTANCE,
            (const char*[]){ "WH_STRUCT_TYPE_STRING",				nullptr },					WH_TYPE_I64, WH_STRUCT_TYPE_STRING,
            (const char*[]){ "WH_STRUCT_TYPE_RGBA",				nullptr },					WH_TYPE_I64, WH_STRUCT_TYPE_RGBA,

            (const char*[]){ "WH_STRUCT_TYPE_BUFFER",				nullptr },					WH_TYPE_I64, WH_STRUCT_TYPE_BUFFER,
            (const char*[]){ "WH_STRUCT_TYPE_IMG_PNG",			nullptr },					WH_TYPE_I64, WH_STRUCT_TYPE_IMG_PNG,

            // functions
            (const char*[]){ "WH", "file", "read",						nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_file_read,
            (const char*[]){ "WH", "file", "dir", "read",			nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_dir_read,
            (const char*[]){ "WH", "file", "dir", "close",			nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_dir_close,
            (const char*[]){ "WH", "maths", "int", "pos",			nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_intpos,
            (const char*[]){ "WH", "maths", "int", "pow",			nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_intpow,
            (const char*[]){ "WH", "maths", "hash", "simple",		nullptr },					WH_TYPE_FUNCTION_PTR, &wh_lua_hash_simple
        );
    return 0;
}

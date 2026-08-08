#ifndef _wh_header_lua_config_
#define _wh_header_lua_config_

#include<wh-types/config.h>
#include<wh/headers/lua.h>

typedef struct {
    lua_State* ls;
    const char* table;
    int index;
} _wh_lua_add_ints_params;

typedef struct {
    lua_State* ls;
    const char* table;
    int index;
} _wh_lua_add_uints_params;

typedef struct {
    lua_State* ls;
    const char* table;
    int index;
} _wh_lua_add_bools_params;

typedef struct {
    lua_State* ls;
    wh_config_s* config;
} _wh_config_lua_expose_params;

extern i8 _wh_lua_add_ints(_wh_lua_add_ints_params params, ...);
extern i8 _wh_lua_add_uints(_wh_lua_add_uints_params params, ...);
extern i8 _wh_lua_add_bools(_wh_lua_add_bools_params params, ...);

extern i8 _wh_config_lua_expose(_wh_config_lua_expose_params params);

/* [MD_DOC]
 * # wh_lua_add_ints
 * ```c
 * i8 wh_lua_add_ints(lua_State* ls, const char* table, int index, ...)
 * ```
 *
 * @d_param(lua_State)		ls		: The Lua state that will be used.
 * @d_param(const char*)	table	: The table where the values will live.
 * @d_param(int)				index	:
 *
 * ## Return values
 *
 */
#define wh_lua_add_ints(x, ...) WH_EFP(_wh_lua_add_ints((_wh_lua_add_ints_params) { WH_VA_ARGS x } __VA_OPT__(, __VA_ARGS__), nullptr))

/* [MD_DOC]
 * # wh_lua_add_uints
 * ```c
 * i8 wh_lua_add_uints(lua_State* ls, const char* table, int index, ...)
 * ```
 *
 * @d_param(lua_State)		ls		: The Lua state that will be used.
 * @d_param(const char*)	table	: The table where the values will live.
 * @d_param(int)				index	:
 *
 * ## Return values
 *
 */
#define wh_lua_add_uints(x, ...) WH_EPF(_wh_lua_add_uints((_wh_lua_add_uints_params) { WH_VA_ARGS x } __VA_OPT__(, __VA_ARGS__), nullptr))

/* [MD_DOC]
 * # wh_lua_add_bool
 * ```c
 * i8 wh_lua_add_bools(lua_State* ls, const char* table, int index, ...)
 * ```
 *
 * @d_param(lua_State)		ls		: The Lua state that will be used.
 * @d_param(const char*)	table	: The table where the values will live.
 * @d_param(int)				index	:
 *
 * ## Return values
 *
 */
#define wh_lua_add_bools(x, ...) WH_EPF(_wh_lua_add_bools((_wh_lua_add_bools_params) { WH_VA_ARGS x } __VA_OPT__(, __VA_ARGS__), nullptr))

#define wh_config_lua_expose(...) WH_EPF(_wh_config_lua_expose((_wh_config_lua_expose_params) { __VA_ARGS__ }))


#endif /* _wh_header_lua_config_ */

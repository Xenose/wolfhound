#ifndef _wh_header_lua_api_filesystem_
#define _wh_header_lua_api_filesystem_

#include<wh/headers/lua.h>

WH_C()

extern int wh_lua_dir_read(lua_State* ls);
extern void wh_lua_dir_close(lua_State* ls);

WH_C_END()

#endif /* _wh_header_lua_api_filesystem_ */
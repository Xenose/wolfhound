#ifndef _wh_header_lua_api_filesystem_
#define _wh_header_lua_api_filesystem_

#include<lua.h>

extern int wh_lua_dir_read(lua_State* ls);
extern void wh_lua_dir_close(lua_State* ls);

#endif /* _wh_header_lua_api_filesystem_ */

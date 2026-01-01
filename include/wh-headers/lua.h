#ifndef _wh_headers_lua_
#define _wh_headers_lua_

#include<wh-common/os.h>

#if (WH_SYSTEM&WH_SYS_FREEBSD)
	#include<lua54/lua.h>
	#include<lua54/lualib.h>
	#include<lua54/lauxlib.h>
#else
	#include<lua.h>
	#include<lualib.h>
	#include<lauxlib.h>
#endif

#endif

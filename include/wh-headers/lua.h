#ifndef _wh_headers_lua_
#define _wh_headers_lua_

#include<wh-common/os.h>

#if (WH_SYSTEM&WH_SYS_FREEBSD)
	#include<sys/lua.h>
	#include<sys/lualib.h>
	#include<sys/lauxlib.h>
#else
	#include<lua.h>
	#include<lualib.h>
	#include<lauxlib.h>
#endif

#endif

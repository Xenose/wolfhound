INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

WH_FIND_V2(
	"lua"
	"liblua;lua;Lua;lua54;lua53;liblua-5.4;liblua-5.3;lua-5.4;lua5.4;lua-5.3;lua5.3;lua.5.1;lua51"
	"lua.h;lualib.h"
	"lua5.4;lua5.4;lua5.3;lua5.3;lua;lua54;lua53"
	FALSE 
	WH_LUA_LIB 
	WH_LUA_INC
)

IF(WH_LUA_LIB)
	LIST(APPEND WH_LIBS ${WH_LUA_LIB})
	LIST(APPEND WH_INCLUDES ${WH_LUA_INC})
	LIST(APPEND LUA_SOURCES ${C_SOURCES})
ELSE()
	LIST(APPEND WH_DEFS "WH_LUA_NOT_FOUND")
ENDIF()

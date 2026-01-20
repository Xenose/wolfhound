INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

SET(LIB_NAME_ALTS lua54 lua53 liblua-5.4 liblua-5.3 lua-5.4 lua5.4 lua-5.3 lua5.3 lua.5.1 lua51 lua)
SET(LIB_HEADER_NAMES lua.h lualib.h)
SET(INCLUDE_PREFIX lua5.4 lua5.4 lua5.3 lua5.3 lua lua54 lua53)
WH_FIND_LIB(Lua)

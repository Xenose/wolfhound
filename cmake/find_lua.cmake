INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

SET(LIB_NAME_ALTS lua lua5.4 lua54 lua5.3 lua53)
SET(LIB_HEADER_NAMES lua.h lualib.h)
SET(INCLUDE_PREFIX lua5.4 lua54 lua5.3 lua53 lua)
WH_FIND_LIB(Lua)

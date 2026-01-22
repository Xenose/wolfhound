INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

#SET(LIB_NAMES_ALT sdl3 SDL3 libSDL3)
#SET(LIB_HEADER_NAMES sdl3.h SDL.h)
#SET(INCLUDE_PREFIX SDL3)
#WH_FIND_LIB(SDL3)

WH_FIND_V2(
	"sdl3"										# Name of the library
	"sdl3;SDL3;libSDL3"						# Possible names on the system
	"sdl3.h;SDL.h"								# Possible names of the headers
	"sdl3;SDL3"									# Possible folder names
	FALSE											# Disables the library
	WH_SDL_LIB									# Output variable for the library
	WH_SDL_INC									# Output variable for the headers
)

IF(WH_UNWIND_LIB)
	LIST(APPEND WH_LIBS ${WH_SDL_LIB})
	LIST(APPEND WH_INCLUDES ${WH_SDL_INC})
	LIST(APPEND SDL_SOURCES ${C_SOURCES})
ELSE()
	LIST(APPEND WH_DEFS "WH_SDL_NOT_FOUND")
ENDIF()

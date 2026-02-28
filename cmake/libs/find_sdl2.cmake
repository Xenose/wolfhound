INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

WH_FIND_V2(
	"SDL2"										# Name of the library
	"sdl2;SDL2;libSDL2"						# Possible names on the system
	"sdl2.h;SDL.h"								# Possible names of the headers
	"sdl2;SDL2"									# Possible folder names
	FALSE											# Disables the library
	WH_SDL2_LIB									# Output variable for the library
	WH_SDL2_INC									# Output variable for the headers
)

IF(WH_SDL2_LIB)
	LIST(APPEND WH_LIBS ${WH_SDL2_LIB})
	LIST(APPEND WH_INCLUDES ${WH_SDL2_INC})
	LIST(APPEND C_SOURCES ${SDL2_SOURCES})
	
	MESSAGE(STATUS "WH_LIBS = ${WH_LIBS}")
	LIST(APPEND WH_DEFS "WH_SDL2_FOUND")
ENDIF()

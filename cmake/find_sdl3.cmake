FIND_LIBRARY(LIB_SDL3
	NAMES sdl3 SDL3
)


IF (NOT LIB_SDL3)
	#IF (WIN32)
	#	FILE(DOWNLOAD "https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_Win64_dll17_lib.zip/download" "c:/tmp")
	#ENDIF()

	FIND_LIBRARY(LIB_SDL3
		NAMES sdl3 SDL3 libSDL3 libgtest)
ENDIF ()

TARGET_LINK_LIBRARIES(${APP_NAME} INTERFACE ${LIB_SDL3})

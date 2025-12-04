INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

SET(LIB_NAMES_ALT sdl3 SDL3 libSDL3)
SET(HEADER_NAMES_ALT sdl3.h SDL3/SDL.h)
WH_FIND_LIB(SDL3)



# FIND_PACKAGE(SDL3)
# 
# IF(SDL3_FOUND)
# 	MESSAGE(STATUS "Found SDL3 (Version ${SDL3_VERSION})")
# 	LIST(APPEND WH_LIBS SDL3::SDL3)
# 	LIST(APPEND C_SOURCES ${SLD3_SOURCES})
# ELSE()
# 	INCLUDE(CheckIncludeFile)
# 	SET(LIBRARY_NAMES sdl3 SDL3 libSDL3)
# 
# 	CHECK_INCLUDE_FILE("SDL3/SDL.h" HAVE_SDL3_HEADER)
# 
# 	IF(NOT HAVE_SDL3_HEADER)
# 		MESSAGE("SDL3 header not found. SDL3 features will be disabled.")
# 		LIST(APPEND WH_DEFS WH_SDL3_NOT_FOUND)
# 	ELSE()
# 		MESSAGE("SDL3 headers found!")
# 		#IF (WIN32)
# 		#	FILE(DOWNLOAD "https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_Win64_dll17_lib.zip/download" "c:/tmp")
# 		#ENDIF()
# 
# 		FIND_LIBRARY(LIB_SDL3
# 			NAMES ${LIBRARY_NAMES}
# 			PATH_SUFFIXES Lib lib
# 		)
# 
# 		IF(NOT LIB_SDL3)
# 			# TODO download
# 
# 			FIND_LIBRARY(LIB_SDL3
# 				NAMES ${LIBRARY_NAMES}
# 			)
# 		ENDIF()
# 
# 		IF(NOT LIB_SDL3)
# 			MESSAGE(WARNING "SDL3 library not found. SDL3 features will be disabled.")
# 			LIST(APPEND WH_DEFS WH_SDL3_NOT_FOUND)
# 		ELSE()
# 			LIST(APPEND WH_LIBS ${LIB_SDL3})
# 			LIST(APPEND C_SOURCES ${SDL3_SOURCES})
# 		ENDIF()
# 	ENDIF ()
# ENDIF()

CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C )#Fortran)


# Telling CMake that we use C and Fortran
# Adding Fortran Support
# ENABLE_LANGUAGE(Fortran)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)
# We will use a new version of C do
SET(CMAKE_C_STANDARD 23)
SET(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE(cmake/windows.cmake)

set(F95_SOURCES
)

set(C_SOURCES
	"src/wolfhound.c"
	"src/debug/signalar.c"
	"src/game/actions.c"
	"src/game/entity.c"
	"src/sys/library.c"
	"src/sys/memory.c"
	"src/sys/info.c"
	"src/maths/memory.c"
	"src/memory/arena.c"
	"src/memory/freelist.c"
	"src/raylib/debug.c"
	"src/raylib/raylib.c"
	"src/raylib/render.c"
	"src/raylib/window.c"
	"src/sdl3/render.c"
	"src/lua/api/file.c"
	"src/lua/api/maths.c"
	"src/lua/api.c"
	"src/lua/config.c"
	"src/lua/helpers.c"
	"src/arg_parser.c"
	"src/config.c"
	"src/convert.c"
	"src/debug.c"
	"src/error.c"
	"src/file.c"
	"src/maths.c"
	"src/memory.c"
	"src/string.c"
	"src/render.c"
	"src/vulkan.c"
	"src/print.c"
	"src/window.c"
	"src/wrap/unistd.c"
	"src/wrap/string.c"
)

ADD_LIBRARY(${APP_NAME} INTERFACE)

IF(F95_SOURCES)
	# Create a library from Fortran sources
	add_library(source_f95 STATIC ${F95_SOURCES})
	target_include_directories(source_f95 PUBLIC "include")
	target_link_libraries(${APP_NAME} INTERFACE "source_f95")
ENDIF()

IF(C_SOURCES)
	# Create a library from C sources
	add_library(source_c STATIC ${C_SOURCES})
	target_include_directories(source_c PUBLIC "include")
	target_link_libraries(${APP_NAME} INTERFACE "source_c")
ENDIF()

# Library search
INCLUDE(cmake/find_lua.cmake)
INCLUDE(cmake/find_sdl3.cmake)
INCLUDE(cmake/find_vulkan.cmake)
INCLUDE(cmake/find_unwind.cmake)

# Link the C library with the Fortran library
IF(WIN32)
	TARGET_LINK_LIBRARIES(${APP_NAME} INTERFACE)
ELSE()
	TARGET_LINK_LIBRARIES(${APP_NAME} INTERFACE "m" "dl" "atomic" "bsd")
ENDIF()

# Projects to build
ADD_SUBDIRECTORY(example/chess)
ADD_SUBDIRECTORY(example/print)

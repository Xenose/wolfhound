CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C CXX)

INCLUDE(CheckLanguage)

# Telling CMake that we use C and Fortran
# Adding Fortran Support
CHECK_LANGUAGE(Fortran)

# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)
# We will use a new version of C do
SET(CMAKE_C_STANDARD 23)
SET(CMAKE_C_STANDARD_REQUIRED ON)

# Lets use the new C++ as well
SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

INCLUDE_DIRECTORIES(SYSTEM "include/")

IF (WIN32)
	MESSAGE("\n\tWE ARE ON WINDOWS!")

	#MAKE_DIRECTORY("C:/usr/include/")
	#MAKE_DIRECTORY("C:/usr/lib/")
	#MAKE_DIRECTORY("C:/tmp/")

	# having the include same as Unix / Linux make more sense
	INCLUDE_DIRECTORIES(SYSTEM "C:/usr/include/")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};C:/usr/lib")
	#LINK_DIRECTORIES(AFTER "C:/usr/lib/")

	# More Windows Magic for atomics :: Legacy KEEP
	IF (MSVC)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /experimental:c11atomics")
	ENDIF()
ENDIF()

# checking if we have Fortran on the system
IF(CMAKE_Fortran_COMPILER)
	MESSAGE(STATUS "Fortran compiler found: ${CMAKE_Fortran_COMPILER}")
	ENABLE_LANGUAGE(Fortran)
	#ADD_COMPILE_DEFINITIONS(WH_USE_FORTRAN=1)
	SET(USE_FORTRAN ON)
ELSE()
	MESSAGE(WARNING "Fortran compiler NOT found. Falling back to C implementations.")
	SET(USE_FORTRAN OFF)
ENDIF()

set(F95_SOURCES
	"src/maths/core.f95"
)

set(C_SOURCES
	"src/loader/asset.c"
	"src/wolfhound.c"
	"src/debug/signalar.c"
	"src/game/actions.c"
	"src/game/entity.c"
	"src/game/loader.c"
	"src/sys/library.c"
	"src/sys/memory.c"
	"src/sys/info.c"
	"src/sys/filesystem.c"
	"src/maths/core.c"
	"src/maths/memory.c"
	"src/memory/arena.c"
	"src/memory/freelist.c"
	"src/raylib/debug.c"
	"src/raylib/render.c"
	"src/raylib/window.c"
	"src/sdl3/render.c"
	"src/lua/api/file.c"
	"src/lua/api/maths.c"
	"src/lua/api.c"
	"src/lua/config.c"
	"src/lua/helpers.c"
	"src/images/loader.c"
	"src/arg_parser.c"
	"src/config.c"
	"src/convert.c"
	"src/debug.c"
	"src/error.c"
	"src/file.c"
	"src/memory.c"
	"src/string.c"
	"src/render.c"
	"src/print.c"
	"src/window.c"
	"src/wrap/unistd.c"
	"src/wrap/string.c"
)

set(CXX_SOURCES
	"src/cpp/wolfhound.cpp"
)

SET(VULKAN_SOURCES
	"src/vulkan.c"
)


IF(USE_FORTRAN)
	ADD_LIBRARY(${APP_NAME} STATIC ${C_SOURCES} ${CXX_SOURCES} ${F95_SOURCES})
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PRIVATE WH_USE_FORTRAN=1)
ELSE()
	ADD_LIBRARY(${APP_NAME} STATIC ${C_SOURCES} ${CXX_SOURCES})
ENDIF()

# Library search
INCLUDE(cmake/find_lua.cmake)
INCLUDE(cmake/find_sdl3.cmake)
INCLUDE(cmake/find_glew.cmake)
INCLUDE(cmake/find_vulkan.cmake)
INCLUDE(cmake/find_unwind.cmake)

# Link the C library with the Fortran library
IF(WIN32)
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE)
ELSE()
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE "m" "dl" "atomic" "bsd")
ENDIF()

# -----------------------------------------------------------------------------
# Example Subprojects
# These subprojects (e.g., example/chess, example/print) demonstrate usage of
# the 'wolfhound' interface library. They are built as standalone executables
# or examples and link against the core libraries defined above.
# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY(example/chess)
ADD_SUBDIRECTORY(example/print)
ADD_SUBDIRECTORY(example/cpp)

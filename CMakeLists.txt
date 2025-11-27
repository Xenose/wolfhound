CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C CXX)

INCLUDE(CheckLanguage)

OPTION(NO_CXX_COMPILER "Disbles the C++ compiler" False)
OPTION(LINUX_MINGW_WIN "Disbles the C++ compiler" False)

# Telling CMake that we use C and Fortran
# Adding Fortran Support
CHECK_LANGUAGE(Fortran)
# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)
SET(CMAKE_C_STANDARD_REQUIRED ON)

# Lets use the new C++ as well
IF (NOT NO_CXX_COMPILER)
	SET(CMAKE_CXX_STANDARD 23)
	SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
INCLUDE_DIRECTORIES(SYSTEM "include/")

IF (LINUX_MINGW_WIN)
	MESSAGE("\n\tWE ARE COMPILING FOR WINDOWS!")
	MESSAGE(STATUS "-- Cross-compiling from Linux to Windows (MinGW)")

	INCLUDE_DIRECTORIES(SYSTEM "/opt/windows/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};/opt/windows/lib")
	SET(USE_FORTRAN OFF)
ELSEIF(WIN32)
	MESSAGE("\n\tWE ARE ON WINDOWS!")

	#MAKE_DIRECTORY("C:/usr/include/")
	#MAKE_DIRECTORY("C:/usr/lib/")
	#MAKE_DIRECTORY("C:/tmp/")

	# having the include same as Unix / Linux make more sense
	INCLUDE_DIRECTORIES(SYSTEM "C:/usr/include/" "include/" "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/VC/Tools/MSVC/14.44.35207/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};C:/usr/lib")
	#LINK_DIRECTORIES(AFTER "C:/usr/lib/")

	# More Windows Magic for atomics :: Legacy KEEP
	IF (MSVC)
		SET(CMAKE_C_STANDARD 17)
		SET(CMAKE_C_FLAGS 
			"${CMAKE_C_FLAGS}" 
			"/experimental:c11atomics"
			"/experimental:preprocessor"
		)
	ELSE()
		SET(CMAKE_C_STANDARD 23)
	ENDIF()
ELSE()
	MESSAGE("\n\tWE ARE NOT ON WINDOWS!")
	SET(CMAKE_C_STANDARD 23)

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
ENDIF()

set(F95_SOURCES
	"src/engine/maths/core.f95"
)

set(C_SOURCES
	"src/engine/arg_parser.c"
	"src/engine/config.c"
	"src/engine/convert.c"
	"src/engine/data/hashmap_lazy.c"
	"src/engine/debug/benchmark.c"
	"src/engine/debug/error.c"
	"src/engine/debug/logger.c"
	"src/engine/debug/signalar.c"
	"src/engine/file.c"
	"src/engine/debug/exceptions.c"
	"src/engine/game/actions.c"
	"src/engine/game/entity.c"
	"src/engine/game/loader.c"
	"src/engine/images/loader.c"
	"src/engine/loader/asset.c"
	"src/engine/lua/api.c"
	"src/engine/lua/api/file.c"
	"src/engine/lua/api/filesystem.c"
	"src/engine/lua/api/maths.c"
	"src/engine/lua/config.c"
	"src/engine/lua/helpers.c"
	"src/engine/maths/core.c"
	"src/engine/maths/memory.c"
	"src/engine/memory.c"
	"src/engine/memory/arena.c"
	"src/engine/memory/core.c"
	"src/engine/memory/freelist.c"
	"src/engine/print.c"
	"src/engine/raylib/debug.c"
	"src/engine/raylib/render.c"
	"src/engine/raylib/window.c"
	"src/engine/render.c"
	"src/engine/sdl3/render.c"
	"src/engine/sdl3/window.c"
	"src/engine/string.c"
	"src/engine/sys/filesystem.c"
	"src/engine/sys/info.c"
	"src/engine/sys/library.c"
	"src/engine/sys/memory.c"
	"src/engine/testing/unite.c"
	"src/engine/window.c"
	"src/engine/wolfhound.c"
	"src/engine/wrap/string.c"
	"src/engine/wrap/unistd.c"
	"src/engine/wrap/time.c"
	"src/engine/network/socket.c"
)

IF (NOT NO_CXX_COMPILER)
	set(CXX_SOURCES
		"src/engine_cpp/wolfhound.cpp"
		"src/engine_cpp/print.cpp"
		"src/engine_cpp/memory.cpp"
		"src/engine_cpp/maths/core.cpp"
	)
ENDIF()

SET(VULKAN_SOURCES
	"src/engine/vulkan.c"
)

FOREACH(src_file IN LISTS C_SOURCES CXX_SOURCES)
	GET_FILENAME_COMPONENT(basename ${src_file} NAME)
	SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_DEFINITIONS "__FILENAME__=\"${basename}\"")
ENDFOREACH()

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

IF(WIN32)
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE)

	IF (MSVC)
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			-Wall
			
			-wd4100
			-wd5110
		)
	ELSE()
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			--target=x86_64-pc-windows-gnu

			-Wall
			-Wextra
			-Wpedantic
			-Wconversion
			-Wshadow

			-Wno-implicit-fallthrough
			-Wno-unused-label
			-Wno-unused-variable
			-Wno-unused-parameter
			-Wno-unused-but-set-variable

			# In C +99 structs are zero out
			# -Wno-missing-field-initializers

			-O0
		)
	ENDIF()
ELSE()
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE "m" "dl" "atomic" "bsd" "gcov")
	TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
		-Wshadow

		-Wno-implicit-fallthrough
		-Wno-unused-label
		-Wno-unused-variable
		-Wno-unused-parameter
		-Wno-unused-but-set-variable

		# In C +99 structs are zero out
		# -Wno-missing-field-initializers

		-O0
	)
ENDIF()

IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT)
	MESSAGE(STATUS "Enabling coverage flags for GCC/Clang")
	TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE --coverage -g)
	TARGET_LINK_OPTIONS(${APP_NAME} PRIVATE --coverage)
ENDIF()

# -----------------------------------------------------------------------------
# Example Subprojects
# These subprojects (e.g., example/chess, example/print) demonstrate usage of
# the 'wolfhound' interface library. They are built as standalone executables
# or examples and link against the core libraries defined above.
# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY(src/example/chess)
ADD_SUBDIRECTORY(src/example/gameobject)
ADD_SUBDIRECTORY(src/example/memory)
ADD_SUBDIRECTORY(src/example/print)
ADD_SUBDIRECTORY(src/example/socket_server)
ADD_SUBDIRECTORY(src/example/socket_client)

# C++ examples
IF (NOT NO_CXX_COMPILER)
	ADD_SUBDIRECTORY(src/example/cpp)

	# For now GTEST is not supported on windows.
	IF (NOT WIN32)
		ADD_SUBDIRECTORY(src/tests/cpp/gtests/)
	ENDIF()
ENDIF()

# Tests
# ADD_SUBDIRECTORY(tests/c/unit_tests/)

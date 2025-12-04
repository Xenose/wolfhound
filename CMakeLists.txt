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

SET(CMAKE_C_STANDARD 23)
SET(CMAKE_C_STANDARD_REQUIRED ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(WIN_SYSROOT "C:/usr" CACHE PATH "Windows sysroot directory")
SET(WINUX_SYSROOT "/opt/windows/" CACHE PATH "MinGW cross-sysroot on Linux")

SET(MSVC_FLAGS	
	-Wall
	-wd4100
	-wd5110
)

SET(NON_MSVC_FLAGS
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
)

# Lets use the new C++ as well
IF (NOT NO_CXX_COMPILER)
	SET(CMAKE_CXX_STANDARD 23)
	SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_SOURCE_DIR}/include/")

IF (LINUX_MINGW_WIN)
	MESSAGE("\n\tWE ARE COMPILING FOR WINDOWS!")
	MESSAGE(STATUS "-- Cross-compiling from Linux to Windows (MinGW)")

	INCLUDE_DIRECTORIES(SYSTEM "${WINUX_SYSROOT}/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};/opt/windows/lib")
	SET(USE_FORTRAN OFF)
ELSEIF(WIN32)
	MESSAGE("\n\tWE ARE ON WINDOWS!")

	# having the include same as Unix / Linux make more sense
	INCLUDE_DIRECTORIES(SYSTEM "${WIN_SYSROOT}/include/" "C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/ucrt" "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/VC/Tools/MSVC/14.44.35207/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${WIN_SYSROOT}/lib")
	#LINK_DIRECTORIES(AFTER "C:/usr/lib/")

	# More Windows Magic for atomics :: Legacy KEEP
	IF (MSVC)
		MESSAGE("\tNO ITS MSVC...")
		SET(CMAKE_C_STANDARD 17)
		
		ADD_COMPILE_OPTIONS(
			$<$<C_COMPILER_ID:MSVC>:/experimental:c11atomics>
			$<$<C_COMPILER_ID:MSVC>:/Zc:preprocessor>
		)
	ENDIF()
ELSE()
	MESSAGE("\n\tWE ARE NOT ON WINDOWS!")

	# checking if we have Fortran on the system
	IF(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
		MESSAGE(WARNING "TCC Fortran turned off.")
		SET(USE_FORTRAN OFF)
	ELSEIF(CMAKE_Fortran_COMPILER)
		MESSAGE(STATUS "Fortran compiler found: ${CMAKE_Fortran_COMPILER}")
		ENABLE_LANGUAGE(Fortran)
		#ADD_COMPILE_DEFINITIONS(WH_USE_FORTRAN=1)
		SET(USE_FORTRAN ON)
	ELSE()
		MESSAGE(WARNING "Fortran compiler NOT found. Falling back to C implementations.")
		SET(USE_FORTRAN OFF)
	ENDIF()
ENDIF()

IF(USE_FORTRAN)
	SET(F95_SOURCES
		"src/engine/maths/core.f95"
	)
ENDIF()

SET(WH_LIBS)
SET(WH_DEFS)

SET(C_SOURCES
	"src/engine-posix/string.c"
	"src/engine-posix/time.c"
	"src/engine-posix/unistd.c"
	"src/engine-sys/file.c"
	"src/engine-sys/filesystem.c"
	"src/engine-sys/info.c"
	"src/engine-sys/library.c"
	"src/engine-sys/memory.c"
	"src/engine-sys/socket.c"

	"src/engine-testing/exceptions.c"
	"src/engine-testing/unite.c"

	"src/engine/arg_parser.c"
	"src/engine/config.c"
	"src/engine/convert.c"
	"src/engine/data/hashmap_lazy.c"
	"src/engine/debug/benchmark.c"
	"src/engine/debug/error.c"
	"src/engine/debug/logger.c"
	"src/engine/debug/signalar.c"
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
	"src/engine/render.c"
	"src/engine/string.c"
	"src/engine/window.c"
	"src/engine/wolfhound.c"
)

SET (VULKAN_SOURCES
	"src/engine-backends/vulkan/vulkan.c"
)

SET(RAYLIB_SOURCES
	"src/engine-backends/raylib/debug.c"
	"src/engine-backends/raylib/render.c"
	"src/engine-backends/raylib/window.c"
)

SET(SDL3_SOURCES
	"src/engine-backends/sdl3/render.c"
	"src/engine-backends/sdl3/window.c"
)

IF (NOT NO_CXX_COMPILER)
	SET(CXX_SOURCES
		"src/engine-cpp/wolfhound.cpp"
		"src/engine-cpp/print.cpp"
		"src/engine-cpp/memory.cpp"
		"src/engine-cpp/maths/core.cpp"
	)
ENDIF() 

# defines the macro __FILENAME__ for all the files
FOREACH(src_file IN LISTS C_SOURCES CXX_SOURCES)
	GET_FILENAME_COMPONENT(basename ${src_file} NAME)
	SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_DEFINITIONS "__FILENAME__=\"${basename}\"")
ENDFOREACH()

# Library search
INCLUDE(cmake/find_lua.cmake)
INCLUDE(cmake/find_sdl3.cmake)
INCLUDE(cmake/find_glew.cmake)
INCLUDE(cmake/find_vulkan.cmake)
INCLUDE(cmake/find_unwind.cmake)

ADD_LIBRARY(${APP_NAME} STATIC ${C_SOURCES} ${CXX_SOURCES} ${F95_SOURCES})
TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE ${WH_LIBS})

FOREACH(wh_def IN LISTS WH_DEFS)
	MESSAGE("Defining ${wh_def}")
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PUBLIC ${wh_def}=1)
ENDFOREACH()

IF(WH_INCLUDES)
	MESSAGE(STATUS "Adding collected manual include directories: ${WH_INCLUDES}")
	TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PRIVATE ${WH_INCLUDES})
ENDIF()

IF(USE_FORTRAN)
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PRIVATE WH_USE_FORTRAN=1)
ENDIF()

IF(WIN32)
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE)

	IF (MSVC)
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			${MSVC_FLAGS}
		)
	ELSE()
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			${NON_MSVC_FLAGS}
			--target=x86_64-pc-windows-gnu
			-O0
		)
	ENDIF()
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE "m" "dl" "atomic" "bsd")
	TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
		${NON_MSVC_FLAGS}
		-O0
	)
ELSE()
	IF(CMAKE_C_COMPILER_ID MATCHES "GNU")
		LIST(APPEND NON_MSVC_FLAGS -Wno-missing-field-initializers)
	ENDIF()

	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE "m" "dl" "atomic" "bsd" "gcov")
	TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
		${NON_MSVC_FLAGS}
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
		ADD_SUBDIRECTORY(src/unit-gtests-cpp/)
	ENDIF()
ENDIF()

# Tests
# ADD_SUBDIRECTORY(tests/c/unit_tests/)

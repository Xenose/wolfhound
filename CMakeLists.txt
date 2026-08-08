CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C)

ENABLE_LANGUAGE(ASM_NASM OPTIONAL)

# ------------------------------------------------------------------------------------
#   Options for out cmake
# ------------------------------------------------------------------------------------
OPTION(NO_CXX_COMPILER "Disbles the C++ compiler" False)
OPTION(LINUX_MINGW_WIN "Cross compiles the code for Windows" False)
OPTION(BUILD_EXAMPLES "Builds the example projects" True)

OPTION(NO_SDL3 "Disable SDL3" False)
OPTION(NO_SDL2 "Disable SDL2" False)

OPTION(COMPILER_KEFIR "Kefir doesn't have a CMAKE ID, so this is a work around." False)

# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)

SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(NASM_FLAGS "-w-unknown-warning")
SET(NASM_WARNING_FLAGS "-w+all")

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(WH_LIBS)
SET(WH_DEFS)

SET(LOG_PREFIX "[ Wolfhound ]")
SET(INCLUDE_PATHS "${CMAKE_SOURCE_DIR}/include/")

INCLUDE(cmake/detect_lang.cmake)
INCLUDE(cmake/compilers.cmake)
INCLUDE(cmake/source_files.cmake)

# ------------------------------------------------------------------------------------
#   Defining Macros for each filename
# ------------------------------------------------------------------------------------
FOREACH(src_file IN LISTS C_SOURCES CXX_SOURCES)
    GET_FILENAME_COMPONENT(basename ${src_file} NAME)
    SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_DEFINITIONS "__FILENAME__=\"${basename}\"")
ENDFOREACH()

# ------------------------------------------------------------------------------------
#   Library search
# ------------------------------------------------------------------------------------
INCLUDE(cmake/libs/find_lua.cmake)
INCLUDE(cmake/libs/find_glew.cmake)
INCLUDE(cmake/libs/find_glfw3.cmake)

IF(NOT NO_SDL3)
	INCLUDE(cmake/libs/find_sdl3.cmake)
ENDIF()

INCLUDE(cmake/libs/find_unwind.cmake)

IF (NOT ANDROID OR NOT CMAKE_SYSTEM_NAME STREQUAL "Android")
	INCLUDE(cmake/libs/find_vulkan.cmake)
ENDIF()

# Fallback if SDL3 is not found.
IF (NOT "WH_SDL3_FOUND" IN_LIST WH_DEFS) 
	MESSAGE("Modern SDL3 not found using SDL2.")
	INCLUDE(cmake/libs/find_sdl2.cmake)
ENDIF()

# old way
#INCLUDE_DIRECTORIES(SYSTEM ${INCLUDE_PATHS})
ADD_LIBRARY(${APP_NAME} STATIC ${ASM_SOURCE} ${F95_SOURCES} ${C_SOURCES} ${CXX_SOURCES})
TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PUBLIC ${INCLUDE_PATHS})

IF(WIN32)
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE ws2_32)
ENDIF()

# ------------------------------------------------------------------------------------
#   Compiler definition section
# ------------------------------------------------------------------------------------
IF(COMPILER_KEFIR)
	MESSAGE(STATUS "Compiler set to Kefir")

	# Manually forcing the ID here allows you to use $<C_COMPILER_ID:Kefir> later
	SET(CMAKE_C_COMPILER_ID "Kefir" CACHE STRING "Compiler ID" FORCE)
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PUBLIC __KEFIR__=1)
ENDIF()

FOREACH(wh_def IN LISTS WH_DEFS)
	MESSAGE("Defining ${wh_def}")
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PUBLIC ${wh_def}=1)
ENDFOREACH()

IF(WH_INCLUDES)
	MESSAGE(STATUS "Adding collected manual include directories: ${WH_INCLUDES}")
	TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PUBLIC ${WH_INCLUDES})
ENDIF()

MESSAGE(STATUS "WH_LIBS = ${WH_LIBS}")

# ------------------------------------------------------------------------------------
#  End of compiler definition section
# ------------------------------------------------------------------------------------


# Linking the found libraries
TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE ${WH_LIBS})

# Compiler flags
TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
    # Common flags non windows
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:TinyCC>,$<C_COMPILER_ID:ZIG>,$<C_COMPILER_ID:Clang>>>:
        -g
        -ggdb
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Wno-unused
        -Wno-implicit-fallthrough
        -Wno-unused-but-set-variable
        -Wunused-parameter
        -Wno-unused-variable
        -Wno-unused-function
        -Wno-unused-label
        -Wno-missing-field-initializers
        -Wno-c23-extensions
    >

    # GCC compiler flags
    $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:GNU>>:
        -rdynamic
        -Wformat-security
        # Need to fix for haiku
        # -pg
        -Wno-missing-field-initializers
    >

    # MSVC flags
    $<$<OR:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>:
        -W4
        -experimental:c11atomics
        -Zc:preprocessor
        -wd4100
    >
)

# Allows us to do line coverage testing
IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT AND NOT ${IS_ANDROID})
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
IF (BUILD_EXAMPLES)
	ADD_SUBDIRECTORY(src/example/chess)
	ADD_SUBDIRECTORY(src/example/lists)
	ADD_SUBDIRECTORY(src/example/hashmaps)
	ADD_SUBDIRECTORY(src/example/gameobject)
	ADD_SUBDIRECTORY(src/example/memory)
	ADD_SUBDIRECTORY(src/example/posix)
	ADD_SUBDIRECTORY(src/example/print)
	#ADD_SUBDIRECTORY(src/example/socket_server)
	#ADD_SUBDIRECTORY(src/example/socket_client)

	# C++ examples
	IF (CXX_ENABLED)
		ADD_SUBDIRECTORY(src/example/cpp)
	ENDIF()
ENDIF()

# Tests
IF (CXX_ENABLED)
	# For now GTEST is not supported on windows.
	IF (CMAKE_SYSTEM_NAME STREQUAL "Linux")
		ADD_SUBDIRECTORY(src/unit-gtests-cpp/)
	ENDIF()
ENDIF()

IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT)
	ADD_SUBDIRECTORY(src/unit-tests-c/)
ENDIF()

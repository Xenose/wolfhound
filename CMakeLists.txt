CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C)

ENABLE_LANGUAGE(ASM_NASM OPTIONAL)

OPTION(NO_CXX_COMPILER "Disbles the C++ compiler" False)
OPTION(LINUX_MINGW_WIN "Cross compiles the code for Windows" False)

# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)

SET(CMAKE_C_STANDARD 23)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(NASM_FLAGS "-w-unknown-warning")
SET(NASM_WARNING_FLAGS "-w+all")

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(WH_LIBS)
SET(WH_DEFS)

SET(WIN_SYSROOT "C:/usr" CACHE PATH "Windows sysroot directory")
SET(WINUX_SYSROOT "/opt/windows/" CACHE PATH "MinGW cross-sysroot on Linux")

SET(COMPILER_O_LEVEL -O0)

SET(LOG_PREFIX "[ Wolfhound ]")

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

INCLUDE(cmake/language.cmake)

SET(INCLUDE_PATHS "${CMAKE_SOURCE_DIR}/include/")

MESSAGE("C standard set to ${CMAKE_C_STANDARD}")

IF (LINUX_MINGW_WIN)
	INCLUDE(cmake/os_cross_windows.cmake)
ELSEIF(WIN32)
	# having the include same as Unix / Linux make more sense
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${WIN_SYSROOT}/lib")

	LIST(PREPEND CMAKE_PREFIX_PATH "${WIN_SYSROOT}")
	LIST(APPEND INCLUDE_PATHS "${WIN_SYSROOT}/include/")
	#LINK_DIRECTORIES(AFTER "${WIN_SYSROOT}/lib/")

	INCLUDE(cmake/os_windows.cmake)
ELSE()
	INCLUDE(cmake/os_posix.cmake)
ENDIF()

OS_CONFIGURE()
ENABLE_LANGS()

IF(CXX_ENABLED)
	ADD_COMPILE_DEFINITIONS(WH_USE_CXX=1)
	ENABLE_LANGUAGE(CXX)
ENDIF()

IF(FORTRAN_ENABLED)
	ADD_COMPILE_DEFINITIONS(WH_USE_FORTRAN=1)
	ENABLE_LANGUAGE(Fortran)
ENDIF()

IF(NASM_ENABLED)
	ADD_COMPILE_DEFINITIONS(WH_USE_NASM=1)
	ENABLE_LANGUAGE(ASM_NASM)
ENDIF()

# Source files
INCLUDE(cmake/source_files.cmake)

# defines the macro __FILENAME__ for all the files
FOREACH(src_file IN LISTS C_SOURCES CXX_SOURCES)
	GET_FILENAME_COMPONENT(basename ${src_file} NAME)
	SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_DEFINITIONS "__FILENAME__=\"${basename}\"")
ENDFOREACH()

# Library search
INCLUDE(cmake/find_lua.cmake)
INCLUDE(cmake/find_glew.cmake)
INCLUDE(cmake/find_glfw3.cmake)
INCLUDE(cmake/find_sdl3.cmake)
INCLUDE(cmake/find_unwind.cmake)
INCLUDE(cmake/find_vulkan.cmake)
MESSAGE("\n")

# Legacy fallback
IF (WH_SDL3_NOT_FOUND) 
	INCLUDE(cmake/find_sdl2.cmake)
ELSE()
	LIST(APPEND WH_DEFS "WH_SDL2_NOT_FOUND")
ENDIF()

# old way
#INCLUDE_DIRECTORIES(SYSTEM ${INCLUDE_PATHS})

ADD_LIBRARY(${APP_NAME} STATIC ${ASM_SOURCE} ${C_SOURCES} ${CXX_SOURCES} ${F95_SOURCES})
TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PUBLIC ${INCLUDE_PATHS})

IF(WH_INCLUDES)
	MESSAGE(STATUS "Adding collected manual include directories: ${WH_INCLUDES}")
	TARGET_INCLUDE_DIRECTORIES(${APP_NAME} PUBLIC ${WH_INCLUDES})
ENDIF()

MESSAGE(STATUS "WH_LIBS = ${WH_LIBS}")
TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE ${WH_LIBS})

# ------------------------------------------------------------------------------------
#   Compiler definition section
# ------------------------------------------------------------------------------------
FOREACH(wh_def IN LISTS WH_DEFS)
	MESSAGE("Defining ${wh_def}")
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PUBLIC ${wh_def}=1)
ENDFOREACH()

IF(FORTRAN_ENABLED)
	TARGET_COMPILE_DEFINITIONS(${APP_NAME} PUBLIC WH_USE_FORTRAN=1)
ENDIF()

# ------------------------------------------------------------------------------------
#  End of compiler definition section
# ------------------------------------------------------------------------------------

INCLUDE(cmake/compiler.cmake)
OS_COMPILE()

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
ADD_SUBDIRECTORY(src/example/chess)
ADD_SUBDIRECTORY(src/example/lists)
ADD_SUBDIRECTORY(src/example/hashmaps)
ADD_SUBDIRECTORY(src/example/gameobject)
ADD_SUBDIRECTORY(src/example/memory)
ADD_SUBDIRECTORY(src/example/print)
#ADD_SUBDIRECTORY(src/example/socket_server)
#ADD_SUBDIRECTORY(src/example/socket_client)

# C++ examples
IF (CXX_ENABLED)
	ADD_SUBDIRECTORY(src/example/cpp)

	# For now GTEST is not supported on windows.
	IF (CMAKE_SYSTEM_NAME STREQUAL "Linux")
		ADD_SUBDIRECTORY(src/unit-gtests-cpp/)
	ENDIF()
ENDIF()

# Tests
IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT)
	ADD_SUBDIRECTORY(src/unit-tests-c/)
ENDIF()

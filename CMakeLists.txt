CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
INCLUDE(CheckLanguage)

SET(APP_NAME wolfhound)
PROJECT(${APP_NAME} LANGUAGES C)

ENABLE_LANGUAGE(ASM_NASM OPTIONAL)

OPTION(NO_CXX_COMPILER "Disbles the C++ compiler" False)
OPTION(LINUX_MINGW_WIN "Cross compiles the code for Windows" False)

# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)

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

IF (WIN32)
	MESSAGE("${LOG_PREFIX} WE ARE ON WINDOWS!")

	# More Windows Magic for atomics :: Legacy KEEP
	IF (MSVC)
		MESSAGE("${LOG_PREFIX} NO ITS MSVC...")
	ENDIF()
ELSE()
	MESSAGE("${LOG_PREFIX} WE ARE NOT ON WINDOWS!")

	IF (ANDROID OR CMAKE_SYSTEM_NAME STREQUAL "Android")
		MESSAGE(STATUS "${LOG_PREFIX} Detected Android/Termux environment. Adding Termux prefix.")

		SET(TERMUX_PREFIX "/data/data/com.termux/files/usr" PARENT_SCOPE)
		SET(IS_ANDROID TRUE PARENT_SCOPE)

		LIST(APPEND CMAKE_PREFIX_PATH ${TERMUX_PREFIX})
		LIST(APPEND CMAKE_INCLUDE_PATH "${TERMUX_PREFIX}/include")
		LIST(APPEND CMAKE_LIBRARY_PATH "${TERMUX_PREFIX}/lib")
	ENDIF()
ENDIF()

# Telling CMake that we use C and Fortran, Nasm
# Adding Fortran Support
CHECK_LANGUAGE(Fortran)
CHECK_LANGUAGE(ASM_NASM)

# Lets use the new C++ as well
IF (NO_CXX_COMPILER)
	SET(CXX_ENABLED FALSE)
ELSE()
	MESSAGE("${LOG_PREFIX} C++ is enabled")

	SET(CXX_ENABLED TRUE)
	SET(CMAKE_CXX_STANDARD_REQUIRED ON)
ENDIF()

IF(DEFINED CMAKE_ASM_NASM_COMPILER)
	MESSAGE("${LOG_PREFIX} NASM found: ${CMAKE_ASM_NASM_COMPILER}")
	SET(NASM_ENABLED TRUE PARENT_SCOPE)
ELSE()
	MESSAGE(STATUS "${LOG_PREFIX} NASM not found")
	SET(NASM_ENABLED FALSE PARENT_SCOPE)
ENDIF()

# checking if we have Fortran on the system
IF(CMAKE_C_COMPILER_ID MATCHES "TinyCC")
	MESSAGE(WARNING "${LOG_PREFIX} TCC Fortran turned off.")

	SET(CXX_ENABLED FALSE)
	SET(FORTRAN_ENABLED FALSE)
ELSEIF(CMAKE_Fortran_COMPILER)
	MESSAGE(STATUS "${LOG_PREFIX} Fortran compiler found: ${CMAKE_Fortran_COMPILER}")
	SET(FORTRAN_ENABLED TRUE)
ELSE()
	MESSAGE(WARNING "${LOG_PREFIX} Fortran compiler NOT found. Falling back to C implementations.")
	SET(FORTRAN_ENABLED FALSE)
ENDIF()

SET(INCLUDE_PATHS "${CMAKE_SOURCE_DIR}/include/")

MESSAGE("C standard set to ${CMAKE_C_STANDARD}")

IF (LINUX_MINGW_WIN)
	SET(CMAKE_SYSTEM_NAME Windows)
	SET(CMAKE_SYSTEM_PROCESSOR x86_64)

	MESSAGE("\n\tWE ARE COMPILING FOR WINDOWS!")
	MESSAGE(STATUS "-- Cross-compiling from Linux to Windows (MinGW)")

	INCLUDE_DIRECTORIES(SYSTEM "${WINUX_SYSROOT}/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};/opt/windows/lib")
	SET(USE_FORTRAN OFF)
ELSEIF(WIN32)
	# having the include same as Unix / Linux make more sense
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${WIN_SYSROOT}/lib")

	LIST(PREPEND CMAKE_PREFIX_PATH "${WIN_SYSROOT}")
	LIST(APPEND INCLUDE_PATHS "${WIN_SYSROOT}/include/")
	#LINK_DIRECTORIES(AFTER "${WIN_SYSROOT}/lib/")
ENDIF()

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
# TODO add gvoc
MESSAGE("\n")

# Legacy fallback
IF (WH_SDL3_NOT_FOUND) 
	MESSAGE("Modern SDL3 not found using SDL2.")
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
IF (WIN32)
	SET(LIBS "ntdll")
ELSE()
	SET(LIBS "m" "dl" "atomic")

	# Solaris-specific linking
	IF(CMAKE_SYSTEM_NAME STREQUAL "SunOS")
		LIST(APPEND LIBS "socket" "nsl")
	ENDIF()
ENDIF()


TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE ${LIBS} ${WH_LIBS})

# Setting the C and C++ version
IF (MSVC)
	TARGET_COMPILE_FEATURES(${APP_NAME} PRIVATE c_std_17)

	IF(CXX_ENABLED)
		 TARGET_COMPILE_FEATURES(${APP_NAME} PRIVATE cxx_std_17)
	ENDIF()
ELSE()
	TARGET_COMPILE_FEATURES(${APP_NAME} PRIVATE c_std_23)

	IF(CXX_ENABLED)
		 TARGET_COMPILE_FEATURES(${APP_NAME} PRIVATE cxx_std_23)
	ENDIF()
ENDIF()

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
		-unused-parameter
		-unused-variable
		-Wno-unused-function
		-Wno-unused-label
		-Wno-missing-field-initializers
		-Wno-c23-extensions
	>

	# GCC compiler flags
	$<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:GNU>>:
		-rdynamic
		-Wformat-security
		-pg
		-Wno-missing-field-initializers
	>

	# MSVC flags
	$<$<OR:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>:
		-W4
		-experimental=c11atomics
		-Zc=preprocessor
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

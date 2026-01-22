INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

WH_FIND_V2(
	"Libunwind"									# Name of the library
	"unwind;libunwind;Libunwind"			# Possible names on the system
	"libunwind.h;libunwind-common.h"		# Possible names of the headers
	""												# Possible folder names
	FALSE											# Disables the library
	WH_UNWIND_LIB								# Output variable for the library
	WH_UNWIND_INC								# Output variable for the headers
)

IF(WH_UNWIND_LIB)
	LIST(APPEND WH_LIBS ${WH_UNWIND_LIB})
	LIST(APPEND WH_INCLUDES ${WH_UNWIND_INC})
	LIST(APPEND UNWIND_SOURCES ${C_SOURCES})
	MESSAGE(STATUS "WH_LIBS = ${WH_LIBS}")
ELSE()
	LIST(APPEND WH_DEFS "WH_LIBUNWIND_NOT_FOUND")
ENDIF()

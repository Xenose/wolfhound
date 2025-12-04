INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

SET(LIB_NAMES_ALT vulkan Vulkan vulkan-1)
SET(HEADER_NAMES_ALT vulkan/vulkan.h)
WH_FIND_LIB(VULKAN)

# INCLUDE(CheckIncludeFile)
# 
# SET(LIBRARY_NAMES vulkan Vulkan vulkan-1)
# 
# CHECK_INCLUDE_FILE("vulkan/vulkan.h" HAVE_VULKAN_HEADER)
# 
# IF(NOT HAVE_VULKAN_HEADER)
# 	MESSAGE(WARNING "Vulkan header not found. Vulkan features will be disabled.")
# 	LIST(APPEND WH_DEFS WH_VULKAN_NOT_FOUND)
# ELSE()
# 	MESSAGE("Vulkan headers found!")
# 
# 	FIND_LIBRARY(LIB_VULKAN
# 		NAMES ${LIBRARY_NAMES}
# 		HINTS ENV VULKAN_SDK
# 		PATH_SUFFIXES Lib lib
# 	)
# 
# 	IF(NOT LIB_VULKAN)
# 		# TODO download
# 
# 		FIND_LIBRARY(LIB_VULKAN 
# 			NAMES ${LIBRARY_NAMES}
# 		)
# 	ENDIF()
# 
# 	IF(NOT LIB_VULKAN)
# 		MESSAGE(WARNING "Vulkan library not found. Vulkan features will be disabled.")
# 		LIST(APPEND WH_DEFS WH_VULKAN_NOT_FOUND)
# 	ELSE()
# 		LIST(APPEND WH_LIBS ${LIB_VULAN})
# 		LIST(APPEND C_SOURCES ${VULKAN_SOURCES})
# 	ENDIF()
# ENDIF()

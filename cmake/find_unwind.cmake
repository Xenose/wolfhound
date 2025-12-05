INCLUDE(${CMAKE_CURRENT_LIST_DIR}/find.cmake)

SET(LIB_NAME_ALTS unwind libunwind)
SET(LIB_HEADER_NAMES libunwind.h libunwind-common.h)
WH_FIND_LIB(Libunwind)

CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
PROJECT(compiled_tests LANGUAGES C)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}") #-fprofile-arcs -ftest-coverage")


INCLUDE_DIRECTORIES(SYSTEM "include/")

ADD_EXECUTABLE(compiled_tests
	"src/maths/core.c"
	"src/print.c"
	"src/source.c"
)

IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT)
	MESSAGE(STATUS "Enabling coverage flags for GCC/Clang")
	TARGET_COMPILE_OPTIONS(compiled_tests PRIVATE --coverage -g)
	TARGET_LINK_OPTIONS(compiled_tests  PRIVATE --coverage)
ENDIF()

TARGET_LINK_LIBRARIES(compiled_tests PRIVATE wolfhound)

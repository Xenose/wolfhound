CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
PROJECT(compiled_tests LANGUAGES C)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}") #-fprofile-arcs -ftest-coverage")

INCLUDE_DIRECTORIES(SYSTEM "include/")

ADD_EXECUTABLE(compiled_tests
	"src/maths/core.c"
	"src/source.c"
)

TARGET_LINK_LIBRARIES(compiled_tests PRIVATE wolfhound)

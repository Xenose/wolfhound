CMAKE_MINIMUM_REQUIRED(VERSION 3.28)
PROJECT(compiled_tests LANGUAGES C)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}") #-fprofile-arcs -ftest-coverage")


INCLUDE_DIRECTORIES(SYSTEM "include/")

ADD_EXECUTABLE(compiled_tests
	"src/maths-core.c"
	#"src/memory.c"
	#"src/print.c"
	"src/main.c"
)

FOREACH(src_file IN LISTS C_SOURCES CXX_SOURCES)
	GET_FILENAME_COMPONENT(basename ${src_file} NAME)
	SET_SOURCE_FILES_PROPERTIES(${src_file} PROPERTIES COMPILE_DEFINITIONS "__FILENAME__=\"${basename}\"")
ENDFOREACH()

#IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang" AND GENERATE_REPORT)
#	MESSAGE(STATUS "Enabling coverage flags for GCC/Clang")
#	TARGET_COMPILE_OPTIONS(compiled_tests PRIVATE --coverage -g)
#	TARGET_LINK_OPTIONS(compiled_tests  PRIVATE --coverage)
#ENDIF()

TARGET_LINK_LIBRARIES(compiled_tests PRIVATE wolfhound gtest)

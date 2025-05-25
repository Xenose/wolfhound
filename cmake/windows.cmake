
IF (WIN32)
	MESSAGE("\n\tWE ARE ON WINDOWS!")
	# Sadly we cannot use Fortran we need to tell CMake where it is
	#FIND_PROGRAM(Fortran_COMPILER NAMES ifx ifort gfortran PATHS "C:/Program Files (x86)/Intel/oneAPI/compiler/latest/bin")
	#MESSAGE("Fortran compiler [ ${Fortran_COMPILER} ]")

	#IF (Fortran_COMPILER)
	#	SET(ENV{FC} ${Fortran_COMPILER})
	#ENDIF()

	make_directory("C:/usr/include/")
	make_directory("C:/usr/lib/")
	make_directory("C:/tmp/")

	# having the include same as Unix / Linux make more sense
	INCLUDE_DIRECTORIES(SYSTEM "C:/usr/include/")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};C:/usr/lib")
	#LINK_DIRECTORIES(AFTER "C:/usr/lib/")

	# More Windows Magic
	IF (MSVC)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /experimental:c11atomics")
	ENDIF()
ENDIF()

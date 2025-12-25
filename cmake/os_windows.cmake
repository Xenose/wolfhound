
FUNCTION(OS_CONFIGURE)
	MESSAGE("\n\tWE ARE ON WINDOWS!")

	# having the include same as Unix / Linux make more sense
	INCLUDE_DIRECTORIES(SYSTEM "${WIN_SYSROOT}/include/" "C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/ucrt" "C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/VC/Tools/MSVC/14.44.35207/include")
	SET(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${WIN_SYSROOT}/lib")
	#LINK_DIRECTORIES(AFTER "C:/usr/lib/")

	# More Windows Magic for atomics :: Legacy KEEP
	IF (MSVC)
		MESSAGE("\tNO ITS MSVC...")
		SET(CMAKE_C_STANDARD 17)
		
		ADD_COMPILE_OPTIONS(
			$<$<C_COMPILER_ID:MSVC>:/experimental:c11atomics>
			$<$<C_COMPILER_ID:MSVC>:/Zc:preprocessor>
		)
	ENDIF()
ENDFUNCTION()

FUNCTION(OS_COMPILE) 
	TARGET_LINK_LIBRARIES(${APP_NAME} PRIVATE)

	IF (MSVC)
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			${MSVC_FLAGS}
		)
	ELSE()
		TARGET_COMPILE_OPTIONS(${APP_NAME} PRIVATE
			${NON_MSVC_FLAGS}
			--target=x86_64-pc-windows-gnu
			${COMPILER_O_LEVEL}
		)
	ENDIF()
ENDFUNCTION()

IF(MSVC) # IF WINDOWS
	add_compile_options(
		-Wall
	)
ELSE() # ELSE IF NOT WINDOWS
	add_compile_options(
		-O0
		-g
		-pg
		-ggdb

		## Warnings
		-Wall
		-Wextra
		-pedantic

		# We are focusing on the more important warnings for now
		-Wno-unused
		-Wno-unused-parameter
		-Wno-unused-variable
		-Wno-unused-function
		-Wno-unused-label
		-Wno-missing-field-initializers
		-Wno-c23-extensions
	)

	# If we are using the GNU compiler we can enable more flags
	IF (CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_LANG STREQUAL "C")
		add_compile_options(
		-rdynamic
		-Wformat-security
		)
	ENDIF() # MSVC
ENDIF()



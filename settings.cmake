ENABLE_LANGUAGE(ASM_NASM OPTIONAL)

OPTION(NO_CXX_COMPILER "Disbles the C++ compiler" False)
OPTION(LINUX_MINGW_WIN "Cross compiles the code for Windows" False)

# We want to use Fortran 95 so we select it
SET(CMAKE_Fortran_STANDARD 95)

SET(CMAKE_C_STANDARD 23)
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

SET(MSVC_FLAGS	
	-Wall
	-wd4100
	-wd5110
)

SET(NON_MSVC_FLAGS
	-Wall
	-Wextra
	-Wpedantic
	-Wconversion
	-Wshadow

	-Wno-implicit-fallthrough
	-Wno-unused-label
	-Wno-unused-variable
	-Wno-unused-parameter
	-Wno-unused-but-set-variable
)

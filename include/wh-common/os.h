#ifndef _wh_header_common_os_
#define _wh_header_common_os_

#define WH_SYS_UNIX		0x01L
#define WH_SYS_POSIX		0x02L
#define WH_SYS_GCC		0x04L
#define WH_SYS_CLANG		0x08L
#define WH_SYS_MSVC		0x10L
#define WH_SYS_MINGW		0x20L
#define WH_SYS_TCC		0x40L

#define WH_SYS_LINUX		(0x0100L | WH_SYS_UNIX | WH_SYS_POSIX)
#define WH_SYS_FREEBSD	(0x0200L | WH_SYS_UNIX | WH_SYS_POSIX)
#define WH_SYS_MACOS		(0x0400L | WH_SYS_UNIX | WH_SYS_POSIX)
#define WH_SYS_BSD		(0x0800L | WH_SYS_UNIX | WH_SYS_POSIX)

#define WH_SYS_WINDOWS	(0x1000L)

#if defined(__linux__)
	#define WH_SYSTEM_OS WH_SYS_LINUX
#elif defined(_WIN32)
	#define WH_SYSTEM_OS WH_SYS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#define WH_SYSTEM_OS WH_SYS_MACOS
#elif defined(__FreeBSD__)
	#define WH_SYSTEM_OS WH_SYS_FREEBSD
#elif defined(__unix__)
	#ifdef _POSIX_C_SOURCE
		#define WH_SYSTEM_OS (WH_SYS_UNIX | WH_SYS_POSIX)
	#else
		#define WH_SYSTEM_OS WH_SYS_UNIX 
	#endif
#endif

#ifdef __clang__
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_CLANG)
#elif defined(__TINYC__)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_TCC)
#elif defined(__MINGW32__)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_MINGW)
#elif defined(__GNUC__)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_GCC)
#elif defined(_MSC_VER)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_MSVC)
#else
    #error "Unknown OS: Please add support for your platform to WH_SYSTEM_OS"
#endif

#endif /* _wh_header_common_os_ */

#ifndef _wh_header_common_os_
#define _wh_header_common_os_

#define WH_SYS_UNIX		0x01L
#define WH_SYS_POSIX		0x02L
#define WH_SYS_BSD		0x04L 

#define WH_SYS_GCC		0x008L
#define WH_SYS_CLANG		0x010L
#define WH_SYS_MSVC		0x020L
#define WH_SYS_MINGW		0x040L
#define WH_SYS_TCC		0x080L
#define WH_SYS_KEFIR		0x100L

#define WH_SYS_LINUX		0x0200L
#define WH_SYS_FREEBSD	0x0400L
#define WH_SYS_MACOS		0x0800L
#define WH_SYS_SOLARIS	0x1000L

#define WH_SYS_WINDOWS	0x2000L
#define WH_SYS_BEOS		0x4000L

#if defined(__linux__)
	#define WH_SYSTEM_OS (WH_SYS_LINUX | WH_SYS_UNIX | WH_SYS_POSIX)
#elif defined(_WIN32)
	#define WH_SYSTEM_OS WH_SYS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#define WH_SYSTEM_OS (WH_SYS_MACOS | WH_SYS_UNIX | WH_SYS_POSIX)
#elif defined(__HAIKU__) | defined(__BEOS__)
	#define WH_SYSTEM_OS (WH_SYS_BEOS | WH_SYS_POSIX)
#elif defined(__FreeBSD__)
	#define WH_SYSTEM_OS (WH_SYS_FREEBSD | WH_SYS_BSD | WH_SYS_UNIX | WH_SYS_POSIX)
#elif defined(__sun) || defined(__SVR4) || defined(__illumos__)
	#define WH_SYSTEM_OS (WH_SYS_SOLARIS | WH_SYS_UNIX | WH_SYS_POSIX)
#elif defined(__unix__)
	#ifdef _POSIX_C_SOURCE
		#define WH_SYSTEM_OS (WH_SYS_UNIX | WH_SYS_POSIX)
	#else
		#define WH_SYSTEM_OS WH_SYS_UNIX 
	#endif
#endif

#ifdef __clang__
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_CLANG)
#elif defined(__KEFIR__)
	#define WH_SYSTEM (WH_SYSTEM_OS | WH_SYS_KEFIR)
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

#ifndef _wh_header_types_library_
#define _wh_header_types_library_

#if _WIN32
#include<wh-posix/windows.h>
#endif

typedef struct {
	#ifdef __linux__
		void* _linux;
	#elif _WIN32
		HMODULE _windows;
	#endif
} wh_lib_s;

#endif /* _wh_header_types_library_ */

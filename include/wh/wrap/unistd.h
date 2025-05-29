#ifndef _wh_header_wrap_unistd_
#define _wh_header_wrap_unistd_

#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
	#include<unistd.h>
#elif _WIN32
	#include<io.h>
	#include<windows.h>

	#define write _write

	extern int getpagesize(void);
#endif


#endif /* _wh_header_wrap_unistd_ */

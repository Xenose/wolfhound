#ifndef _wh_header_wrap_unistd_
#define _wh_header_wrap_unistd_

#include<wh/common.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<unistd.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#include<io.h>
	#include<windows.h>

	#define write _write

	extern int getpagesize(void);
#endif


#endif /* _wh_header_wrap_unistd_ */

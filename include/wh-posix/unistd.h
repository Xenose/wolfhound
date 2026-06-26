#ifndef _wh_header_wrap_unistd_
#define _wh_header_wrap_unistd_

#include<wh-common/common.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<unistd.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#include<wh-posix/windows.h>

	#define F_OK 0x0000
	#define R_OK 0x0001
	#define W_OK 0x0002
	#define X_OK 0x0004

	#define write _write

	extern int getpagesize(void);
#endif

#ifndef _GNU_SOURCE
	extern pid_t gettid(void);
#endif

#endif /* _wh_header_wrap_unistd_ */

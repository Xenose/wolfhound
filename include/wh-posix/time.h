#ifndef _wh_header_wrap_time_
#define _wh_header_wrap_time_

#include<time.h>
#include<wh-common/common.h>

WH_C()

#if (WH_SYSTEM&WH_SYS_POSIX)
	#if (WH_SYSTEM&WH_SYS_SOLARIS)
		#define CLOCK_MONOTONIC_COARSE CLOCK_MONOTONIC
	#endif
#else
#include<wh-posix/windows.h>

typedef enum {
	CLOCK_REALTIME,
	CLOCK_MONOTONIC,
	CLOCK_MONOTONIC_COARSE,
} clockid_t;

/*struct timespec {
	time_t tv_sec;
	time_t tv_nsec;
};*/

extern int clock_gettime(clockid_t clockid, struct timespec* tn);

#endif

WH_C_END()
#endif /* _wh_header_wrap_time_ */

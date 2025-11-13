#ifndef _wh_header_wrap_time_
#define _wh_header_wrap_time_

#include<wh/common.h>

#if (WH_SYSTEM & WH_SYS_POSIX)

#include<time.h>

#else

enum {
	CLOCK_REALTIME,
	CLOCK_MONOTONIC
};

struct timespec {
	time_t tv_sec;
	time_t tv_nsec;
};

extern int clock_gettime(clockid_t* clockid, struct timespec* tn);

#endif

#endif /* _wh_header_wrap_time_ */

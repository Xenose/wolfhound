#include<wh-posix/unistd.h>

#if (WH_SYSTEM&WH_SYS_LINUX)

#ifndef _GNU_SOURCE
#include<sys/syscall.h>

pid_t gettid(void) {
	return (pid_t)syscall(SYS_gettid);
}
#endif /* _GNU_SOURCE */

#elif (WH_SYSTEM&WH_SYS_WINDOWS)

int getpagesize(void) {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
}

pid_t gettid(void) {
	return (pid_t)GetCurrentThreadId();
}

#elif (WH_SYSTEM&WH_SYS_BSD)

pid_t gettid(void) {
	return (pid_t)pthread_getthreadid_np();
}

#endif

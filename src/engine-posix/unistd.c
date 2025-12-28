#include<wh-posix/unistd.h>
#include<wh-posix/time.h>
#include<wh/maths/core.h>

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

//int nanosleep() {
//	NtDelayExecution(TRUE, 100);
//}

int usleep(useconds_t usec) {
	LARGE_INTEGER interval = {
		.QuadPart = -(usec * 10)
	};
	NTSTATUS status = NtDelayExecution(true, &interval);
	
	if (STATUS_USER_APC == status) {
		errno = EINTR;
		return -1;
	}

	return 0;
}

int sleep(unsigned int seconds) {
	struct timespec start = { 0 };
	struct timespec end = { 0 };

	clock_gettime(CLOCK_MONOTONIC, &start);
	
	if (WAIT_IO_COMPLETION == SleepEx(seconds * 1000, true)) {
		return 0;
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	return (seconds - (end.tv_sec - start.tv_sec));
}

#elif (WH_SYSTEM&WH_SYS_BSD)

pid_t gettid(void) {
	return (pid_t)pthread_getthreadid_np();
}

#endif

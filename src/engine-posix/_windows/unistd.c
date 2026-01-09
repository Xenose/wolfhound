#include<wh-posix/unistd.h>
#include<wh-posix/time.h>

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

void* memccpy(void* restrict dst, const void* restrict src, int c, size_t n) {
	u8* d = dst;
	u8* s = (u8*)src;
	size_t i = 0;

	for (; i < n; i++) {
		d[i] = s[i];

		if ((u8)c == d[i]) {
			return (void*)&d[i + 1];
		}
	}

	return nullptr;
}

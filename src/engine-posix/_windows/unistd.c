#include<wh-posix/unistd.h>
#include<wh-posix/time.h>

#include<windows.h>

int getpagesize(void) {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return (int)si.dwPageSize;
}

pid_t gettid(void) {
	return (pid_t)GetCurrentThreadId();
}

//int nanosleep() {
//	NtDelayExecution(TRUE, 100);
//}

int usleep(useconds_t usec) {
    // 1. Setup timer
    HANDLE h_timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (!h_timer) return -1;

    LARGE_INTEGER li_due_time;
    // Set wait time (negative for relative)
    li_due_time.QuadPart = -10 * (long long)usec;

    // 2. Set timer
    if (!SetWaitableTimer(h_timer, &li_due_time, 0, NULL, NULL, FALSE)) {
        CloseHandle(h_timer);
        return -1;
    }

    // 3. Block until signal
    // Using simple WaitForSingleObject to ensure we don't return on APCs
    DWORD wait_result = WaitForSingleObject(h_timer, INFINITE);
    
    CloseHandle(h_timer);
    
    // POSIX usleep returns 0 on success, -1 on failure
    return (wait_result == WAIT_OBJECT_0) ? 0 : -1;
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

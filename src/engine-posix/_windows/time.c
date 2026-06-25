#include<wh-posix/time.h>
#include<wh-posix/windows.h>

static LARGE_INTEGER _frenquency_first();

static LARGE_INTEGER _frequency_cache = { 0 };
static LARGE_INTEGER (*_frequency)() = _frenquency_first;

static LARGE_INTEGER _frenquency_cached() {
	return _frequency_cache ;
}

static LARGE_INTEGER _frenquency_first() {
	QueryPerformanceFrequency(&_frequency_cache);
	_frequency = _frenquency_cached;
	return _frequency_cache;
}

int clock_gettime(clockid_t clockid, struct timespec* tp) {
	FILETIME ft = { 0 };
	LARGE_INTEGER q0;
	LARGE_INTEGER q1;
	
	if (nullptr == tp) {
		return -1;
	}

	switch (clockid) {
		case CLOCK_MONOTONIC_COARSE:
		case CLOCK_MONOTONIC:
			q0 = _frequency();
			QueryPerformanceCounter(&q1);

			tp->tv_sec = q1.QuadPart / q0.QuadPart;
			tp->tv_nsec = (q1.QuadPart % q0.QuadPart) * 1'000'000'000ULL / q0.QuadPart;
			break;

		case CLOCK_REALTIME:
			GetSystemTimePreciseAsFileTime(&ft);
			
			q0.LowPart = ft.dwLowDateTime;
			q0.HighPart = ft.dwHighDateTime;

			q0.QuadPart -= 116444736000000000ULL;

			tp->tv_sec  = q0.QuadPart / 10'000'000ULL;
			tp->tv_nsec = (q0.QuadPart % 10'000'000ULL) * 100;
			break;
	}
	
	return 0;
}

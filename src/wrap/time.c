#include<wh/wrap/time.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)

static wh_thread struct timespec _last_time = {0, 0};

int clock_gettime(clockid_t clockid, struct timespec* tn) {
	FILETIME ft = { 0 };
	ULARGE_INTEGER uli = { 0 };

	if (nullptr == tn) {
		return -1;
	}
	
	while (1) {
		GetSystemTimePreciseAsFileTime(&ft);

		uli.LowPart = ft.dwLowDateTime;
		uli.HighPart = ft.dwHighDateTime;

		tn->tv_sec  = uli.QuadPart / 10'000'000ULL;
		tn->tv_nsec = (uli.QuadPart % 10'000'000ULL) * 100;

		// Ensure monotonicity
		if (tn->tv_sec > _last_time.tv_sec ||
			(tn->tv_sec == _last_time.tv_sec && tn->tv_nsec > _last_time.tv_nsec)) {
			break; // time is strictly increasing, exit loop
		}

		// System time went backward or stayed the same → bump by 1 ns
		tn->tv_sec  = _last_time.tv_sec;
		tn->tv_nsec = _last_time.tv_nsec + 1;

		if (tn->tv_nsec >= 1'000'000'000) {
			tn->tv_sec += 1;
			tn->tv_nsec -= 1'000'000'000;
		}
	}

	_last_time = *tn;
	return 0;
}

#endif

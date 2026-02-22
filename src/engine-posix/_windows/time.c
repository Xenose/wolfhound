#include<wh-posix/time.h>
#include<_wh-nt/time.h>

int clock_gettime(clockid_t clockid, struct timespec* tp) {
	wnt_filetime_s ft = { 0 };
	u64 quad0 = 0;
	u64 quad1 = 0;

	if (nullptr == tp) {
		return -1;
	}

	switch (clockid) {
		case CLOCK_MONOTONIC_COARSE:
		case CLOCK_MONOTONIC:
			_wnt_query_performance_frequency(&quad0);
			_wnt_query_performance_counter(&quad1);

			tp->tv_sec = quad1 / quad0;
			tp->tv_nsec = (quad1 % quad0) * 1'000'000'000ULL / quad0;
			break;

		case CLOCK_REALTIME:
			_wnt_get_system_time_precise_as_file_time(&ft);
			
			((u32*)&quad0)[0] = ft.low_date_time;
			((u32*)&quad0)[1] = ft.high_date_time;

			quad0 -= 116444736000000000ULL;

			tp->tv_sec  = quad0 / 10'000'000ULL;
			tp->tv_nsec = (quad0 % 10'000'000ULL) * 100;
			break;
	}
	
	return 0;
}

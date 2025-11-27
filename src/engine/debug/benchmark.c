#include<stdio.h>
#include<wh/debug/benchmark.h>

wh_benchmark_s wh_benchmark_start(i64 count) {
	wh_benchmark_s bench = { 0 };

	if (0 != clock_gettime(CLOCK_MONOTONIC_COARSE, &bench.time_start)) {
		bench.count = count;
	}

	return bench;
}

void wh_benchmark_end(wh_benchmark_s* bench) {
	i64 nsec = 0;
	i64 sec = 0;

	if (0 == clock_gettime(CLOCK_MONOTONIC_COARSE, &bench->time_end)) {
		nsec = bench->time_end.tv_nsec - bench->time_start.tv_nsec;
		sec = bench->time_end.tv_sec - bench->time_start.tv_sec;

		if (0 > nsec) {
			sec -= 1;
			nsec += 1'000'000'000;
		}

		bench->time_delta.tv_sec = (bench->time_delta.tv_sec + sec) / 2;
		bench->time_delta.tv_nsec = (bench->time_delta.tv_nsec + sec) / 2;
	}

	clock_gettime(CLOCK_MONOTONIC_COARSE, &bench->time_start);
	bench->count++;
}

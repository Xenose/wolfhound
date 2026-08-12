#include<wh-posix/stdio.h>
#include<wh/debug/benchmark.h>

/* 
 TODO create assembly file for this
 static inline uint64_t read_tsc(void) {
 uint32_t lo, hi;
 __asm__ __volatile__ ("rdtscp" : "=a" (lo), "=d" (hi) :: "rcx");
 return ((uint64_t)hi << 32) | lo;
 }
*/

wh_benchmark_s wh_benchmark_start(i64 count) {
	wh_benchmark_s bench = { 0 };

	if (0 != clock_gettime(CLOCK_MONOTONIC, &bench.start.time)) {
		bench.count = count;
	}

	if (0 != clock_gettime(CLOCK_MONOTONIC, &bench.current.time)) {
		bench.count = count;
	}

	return bench;
}

void _wh_benchmark_delta(volatile wh_benchmark_s* bench) {
	volatile i64 nsec = 0;
	volatile i64 sec = 0;

	nsec = bench->end.time.tv_nsec - bench->current.time.tv_nsec;
	sec = bench->end.time.tv_sec - bench->current.time.tv_sec;

	if (0 > nsec) { 
		sec -= 1;
		nsec += 1000000000;
	}

	bench->delta.time.tv_sec += sec;
	bench->delta.time.tv_nsec += nsec;

	if (1000000000 < bench->delta.time.tv_nsec) { 
		bench->delta.time.tv_sec += 1;
		bench->delta.time.tv_nsec -= 1000000000;
	}
}

void _wh_benchmark_total(volatile wh_benchmark_s* bench) {
	volatile i64 nsec = 0;
	volatile i64 sec = 0;

	nsec = bench->end.time.tv_nsec - bench->start.time.tv_nsec;
	sec = bench->end.time.tv_sec - bench->start.time.tv_sec;

	if (0 > nsec) { sec -= 1;
		nsec += 1000000000;
	}

	bench->total.time.tv_sec = sec;
	bench->total.time.tv_nsec = nsec;
}

void wh_benchmark_print(wh_benchmark_s* bench) {
	printf(
		"\nstart : sec -> %li, nsec -> %li\n"
		"end   : sec -> %li, nsec -> %li\n"
		"delta : sec -> %li, nsec -> %li\n"
		"total : sec -> %li, nsec -> %li\n",
		bench->start.time.tv_sec, bench->start.time.tv_nsec,
		bench->end.time.tv_sec, bench->end.time.tv_nsec,
		bench->delta.time.tv_sec, bench->delta.time.tv_nsec,
		bench->total.time.tv_sec, bench->total.time.tv_nsec
	);
}

void wh_benchmark_cycle(wh_benchmark_s* bench, i64 total_count) {
	if (0 == clock_gettime(CLOCK_MONOTONIC, &bench->end.time)) {
		_wh_benchmark_delta(bench);

		if (bench->count < total_count) {
			_wh_benchmark_total(bench);

			bench->delta.time.tv_sec /= total_count;
			bench->delta.time.tv_nsec /= total_count;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &bench->current.time);
	bench->count++;
}

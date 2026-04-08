#ifndef _wh_header_debug_benchmark_
#define _wh_header_debug_benchmark_

#include<wh-posix/time.h>
#include<wh-common/common.h>

typedef struct {
	struct timespec time;
} wh_benchmark_stat_s;

typedef struct {
	i64 count;
	wh_benchmark_stat_s delta;
	wh_benchmark_stat_s total;

	wh_benchmark_stat_s start;
	wh_benchmark_stat_s current;
	wh_benchmark_stat_s end;
} wh_benchmark_s;

#define wh_benchmark(x, c) for (*(x) = wh_benchmark_start((c)); (x)->count < (c); wh_benchmark_cycle((x), (c)))

extern wh_benchmark_s wh_benchmark_start(i64 count);
extern void wh_benchmark_print(wh_benchmark_s* bench);
extern void wh_benchmark_cycle(wh_benchmark_s* bench, i64 total_count);

#endif /* _wh_header_debug_benchmark_ */

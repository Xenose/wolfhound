#ifndef _wh_header_debug_benchmark_
#define _wh_header_debug_benchmark_

#include<wh-posix/time.h>
#include<wh/common.h>

typedef struct {
	i64 count;
	struct timespec time_delta;
	struct timespec time_start;
	struct timespec time_end;
} wh_benchmark_s;

#define wh_benchmark(x, c) for (*(x) = wh_benchmark_start((c)); (x)->count < (c); wh_benchmark_end((x)))

extern wh_benchmark_s wh_benchmark_start(i64 count);
extern void wh_benchmark_end(wh_benchmark_s* bench);

#endif /* _wh_header_debug_benchmark_ */

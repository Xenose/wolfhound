#ifndef _wh_header_debug_benchmark_
#define _wh_header_debug_benchmark_

#include<time.h>
#include<wh/common.h>

typedef struct {
	i8 done;
	clock_t time_delta;
	clock_t time_start;
	clock_t time_end;
} wh_benchmark_s;

#define wh_benchmark(x) for (*(x) = wh_benchmark_start(); 0 == (x)->done; wh_benchmark_end((x)))

extern wh_benchmark_s wh_benchmark_start();
extern void wh_benchmark_end(wh_benchmark_s* bench);

#endif /* _wh_header_debug_benchmark_ */

#include<wh/debug/benchmark.h>

wh_benchmark_s wh_benchmark_start() {
	wh_benchmark_s bench = { 0 };

	return bench;
}

void wh_benchmark_end(wh_benchmark_s* bench) {
}

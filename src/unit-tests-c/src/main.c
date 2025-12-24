#include<stdio.h>

#include<wh/debug/logger.h>

#include"main.h"
#include"print.h"
#include"maths-core.h"
#include"memory.h"

i64 (*test_funcs[TEST_COUNT])(i64* failed, i64* passed) = {
	nullptr
};

/*i64 (*bench_funcs[])() = {
	&benchmark_print,
	nullptr
};*/

int main(int arc, char** arv) {
	i64 failed = 0;
	i64 passed = 0; 

	wh_log_set_level(WH_LOG_LEVEL_DEBUG,	0);
	wh_log_set_level(WH_LOG_LEVEL_INFO,		0);
	wh_log_set_level(WH_LOG_LEVEL_NOTICE,	0);

	for (i64 i = 0; nullptr != test_funcs[i]; i++) {
		test_funcs[i](&failed, &passed);
	}

	/*printf("Benchmarking...\n");
	for (i64 i = 0; nullptr != test_funcs[i]; i++) {
		bench_funcs[i]();
	}*/

	printf("%li of %li failed\n", failed, failed + passed);
	return 0;
}

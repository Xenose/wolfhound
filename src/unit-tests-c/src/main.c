#include<stdio.h>

#include<wh/debug/logger.h>

#include"main.h"
#include"print.h"
#include"maths-core.h"
#include"memory.h"

i64 (*test_funcs[TEST_COUNT])(wh_utest_results_s* results) = {
	nullptr
};

/*i64 (*bench_funcs[])() = {
	&benchmark_print,
	nullptr
};*/

int main(int arc, char** arv) {
	wh_utest_results_s results = { 0 };

	wh_log_set_level(WH_LOG_LEVEL_DEBUG,	0);
	wh_log_set_level(WH_LOG_LEVEL_INFO,		0);
	wh_log_set_level(WH_LOG_LEVEL_NOTICE,	0);

	for (i64 i = 0; nullptr != test_funcs[i]; i++) {
		test_funcs[i](&results);
	}

	/*printf("Benchmarking...\n");
	for (i64 i = 0; nullptr != test_funcs[i]; i++) {
		bench_funcs[i]();
	}*/

	printf("%li of %li failed\n", results.failed, results.failed + results.passed);
	return 0;
}

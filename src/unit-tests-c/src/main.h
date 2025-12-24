#ifndef _wh_unit_main_
#define _wh_unit_main_

#include<stdint.h>
#include<wh/common.h>
#include<wh-testing/macros.h>

#define TEST_COUNT 200

extern i64 (*test_funcs[TEST_COUNT])(wh_utest_results_s* results);

// Helper to add unit tests to the test suit
#define ADD_TESTS(__array__) \
__attribute__((constructor)) \
static void reg_func_##__FILE__##__LINE__() { \
	i64 index = 0; \
	i64 func_count = sizeof(__array__) / sizeof(__array__[0]); \
\
	for (i64 i = 0; TEST_COUNT > i; i++) { \
		if (nullptr == test_funcs[i]) { \
			if (index >= func_count) { \
				break; \
			} \
\
			test_funcs[i] = __array__[index++]; \
		} \
	} \
}

#endif /* _wh_unit_main_ */

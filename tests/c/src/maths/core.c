#include<math.h>
#include<stdio.h>
#include<wh/maths/core.h>
#include<wh/testing/macros.h>

void testing_math(i64* failed, i64* passed) {
	WH_TEST_IS_EQUAL(*failed, *passed, 0L, wh_intpos(0, 10));

	for (i64 i = -1'000'000'000, j = 9; i < 0; j--, i /= 10) {
		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(*failed, *passed, j, wh_intpos(i * k, 10));
		}
	}

	for (i64 i = 1, j = 0; i < 1'000'000'000; j++, i *= 10) {
		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(*failed, *passed, j, wh_intpos(i * k, 10));
		}
	}

	for (i64 i = 0; i < 19; i++) {
		WH_TEST_IS_EQUAL(*failed, *passed, (i64)pow(10, i), wh_intpow(i, 10));
	}
}

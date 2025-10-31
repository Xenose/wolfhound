#include<math.h>
#include<stdio.h>
#include<wh/maths/core.h>
#include<wh/testing/macros.h>

i64 testing_math() {
	i64 passed = 0;
	i64 failed = 0;

	for (i64 i = -1'000'000'000, j = 9; i < 1'000'000'000;) {
		if (0 == i) {
			i = 1;
			j = 0;
		} else if (i < 0) {
			j--;
			i /= 10;
		} else {
			j++;
			i *= 10;
		}

		if (-1 == j) {
			continue;
		}

		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(failed, passed, j, wh_int_dec_count(i * k, 10));
		}
	}

	return failed;
}

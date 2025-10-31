#include<math.h>
#include<stdio.h>
#include<wh/maths/core.h>
#include<wh/testing/macros.h>

i8 _testing_int_dec_count(i64* failed, i64 result, i64 in_value, i64 in_base) {
	i64 out = wh_int_dec_count(in_value, in_base);

	if (result != out) {
		printf("[\033[31m Failed \033[0m ] Return value is [ %li ] wanted [ %li ] --> dec_count(%li, %li)\n", out, result, in_value, in_base);
		++*failed;
		return -1;
	}

	printf("[\033[32m PASSED \033[0m ] Return value is [ %li ] wanted [ %li ] --> dec_count(%li, %li)\n", out, result, in_value, in_base);
	return 0;
}

i8 _testing_intpow(i64 result, i64 in_value, i64 in_base) {
	i64 out = wh_intpow(in_value, in_base);

	if (result != out) {
		printf("[\033[31m FAILED \033[0m ] Return value is [ %li ] wanted [ %li ] --> pow(%li, %li)\n", out, result, in_value, in_base);
		return -1;
	}

	printf("[\033[32m PASSED \033[0m ] Return value is [ %li ] wanted [ %li ] --> pow(%li, %li)\n", out, result, in_value, in_base);
	return 0;

}

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

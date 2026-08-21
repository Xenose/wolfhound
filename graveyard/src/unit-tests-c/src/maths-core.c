#include<wh-posix/math.h>

#include<wh/debug/exceptions.h>

#include<wh/maths/core.h>
#include<wh/maths/memory.h>
#include<wh-testing/macros.h>

#include"main.h"

i64 testing_intpos(wh_utest_results_s* results) {
	WH_TEST_IS_EQUAL(results, 0L, wh_intpos(0, 10));

	for (i64 i = -1'000'000'000, j = 9; i < 0; j--, i /= 10) {
		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(results, j, wh_intpos(i * k, 10));
		}
	}

	for (i64 i = 1, j = 0; i < 1'000'000'000; j++, i *= 10) {
		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(results, j, wh_intpos(i * k, 10));
		}
	}

	return 0;
}

i64 testing_intpow(wh_utest_results_s* results) {
	for (i64 i = 0; i < 19; i++) {
		WH_TEST_IS_EQUAL(results, (i64)powl(10, i), wh_intpow(i, 10));
	}

	return 0;
}

i64 testing_hash_simple(wh_utest_results_s* results) {
	WH_TEST_IS_EQUAL(results, 18L, wh_hash_simple("hello", 100))
	WH_TEST_IS_EQUAL(results, 318L, wh_hash_simple("hello", 1000))
	WH_TEST_IS_EQUAL(results, 1318L, wh_hash_simple("hello", 10000))
	
	WH_TEST_IS_EQUAL(results, 27L, wh_hash_simple("h", 100))
	WH_TEST_IS_EQUAL(results, 727L, wh_hash_simple("h", 1000))
	return 0;
}

i64 testing_align(wh_utest_results_s* results) {
	WH_TEST_IS_EQUAL(results, 0L, wh_align(-1, 4096))
	WH_TEST_IS_EQUAL(results, 32L, wh_align(1, 32))
	WH_TEST_IS_EQUAL(results, 4096L, wh_align(32, 4096))
	WH_TEST_IS_EQUAL(results, 8192L, wh_align(8096, 4096))
	return 0;
}

i64 testing_c_fortran_intpos(wh_utest_results_s* results) {
	for (i64 i = 1; i < 1'000'000; i *= 10) {
		for (i64 k = 1; k < 10; k++) {
			WH_TEST_IS_EQUAL(results, wh_c_intpos(i * k, 10), wh_intpos(i * k, 10));
		}
	}
	return 0;
}


static i64 (*funcs[])(wh_utest_results_s* results) = {
	&testing_intpos,
	&testing_intpow,
	&testing_hash_simple,
	&testing_align,
	&testing_c_fortran_intpos,
};

ADD_TESTS(funcs);

#include<math.h>

#include<wh/debug/exceptions.h>

#include<wh/maths/core.h>
#include<wh/maths/memory.h>
#include<wh/testing/macros.h>

void testing_intpos(i64* failed, i64* passed) {
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
}

void testing_intpow(i64* failed, i64* passed) {
	for (i64 i = 0; i < 19; i++) {
		WH_TEST_IS_EQUAL(*failed, *passed, (i64)powl(10, i), wh_intpow(i, 10));
	}
}

void testing_hash_simple(i64* failed, i64* passed) {
	WH_TEST_IS_EQUAL(*failed, *passed, 18L, wh_hash_simple("hello", 100))
	WH_TEST_IS_EQUAL(*failed, *passed, 318L, wh_hash_simple("hello", 1000))
	WH_TEST_IS_EQUAL(*failed, *passed, 1318L, wh_hash_simple("hello", 10000))
	
	WH_TEST_IS_EQUAL(*failed, *passed, 27L, wh_hash_simple("h", 100))
	WH_TEST_IS_EQUAL(*failed, *passed, 727L, wh_hash_simple("h", 1000))
}


void testing_align(i64* failed, i64* passed) {
	WH_TEST_IS_EQUAL(*failed, *passed, 0L, wh_align(-1, 4096))
	WH_TEST_IS_EQUAL(*failed, *passed, 32L, wh_align(1, 32))
	WH_TEST_IS_EQUAL(*failed, *passed, 4096L, wh_align(32, 4096))
	WH_TEST_IS_EQUAL(*failed, *passed, 8192L, wh_align(8096, 4096))
}

i64 testing_math(i64* failed, i64* passed) {
	wh_try {
		testing_intpos(failed, passed);
		testing_intpow(failed, passed);
		testing_hash_simple(failed, passed);
		testing_align(failed, passed);
	} wh_catch(except) {
	}

	return 0;
}

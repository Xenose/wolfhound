#include<stdio.h>
#include<wh_tests/print.h>
#include<wh_tests/maths/core.h>
#include<wh_tests/memory.h>



i64 (*test_funcs[])(i64* failed, i64* passed) = {
	&testing_math,
	&testing_print,
	&testing_memory,
	nullptr
};


int main(int arc, char** arv) {
	i64 failed = 0;
	i64 passed = 0; 

	for (i64 i = 0; nullptr != test_funcs[i]; i++) {
		test_funcs[i](&failed, &passed);
	}

	printf("%li of %li failed\n", failed, failed + passed);
	return 0;
}

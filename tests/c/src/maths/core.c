#include<math.h>
#include<stdio.h>
#include<wh/maths/core.h>

i8 _testing_intlog(i64 result, i64 in_value, i64 in_base) {
	i64 out = wh_intlog(in_value, in_base);

	if (result != out) {
		printf("[\033[31m Failed \033[0m ] Return value is [ %li ] wanted [ %li ] --> log(%li, %li)\n", out, result, in_value, in_base);
		return -1;
	}

	return 0;
}

i64 testing_intlog() {
	i64 failed = 0;

	for (i64 i = 0; i < 10000; i++) {
		if (-1 == _testing_intlog((i64)log(i), i, 10)) {
			++failed;
		}
	}

	return failed;
}

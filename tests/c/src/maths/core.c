#include<stdio.h>
#include<wh/maths/core.h>

i8 testing_intlog(i64 result, i64 in_value, i64 in_base) {
	i64 out = wh_intlog(in_value, in_base);

	if (result != out) {
		printf("[\033[31m Failed \033[0m ] Return value is [ %li ] wanted [ %li ]\n", out, result);
		return -1;
	}

	return 0;
}

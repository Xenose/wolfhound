#include<string.h>
#include<wh/maths/core.h>

#include<stdio.h>

#ifdef WH_USE_FORTRAN
	extern int64_t _wh_fortran_intpos64(int64_t base, int64_t value);
	extern int64_t _wh_fortran_intpow64(int64_t power, int64_t times);
#endif

i64 _wh_c_intpos(_wh_intpos_params params) {
	// TODO improve the C code
	i64 out = 0;

	if (0 == params.base) {
		params.base = 10;
	}

	params.value = wh_abs(params.value);

	while (params.value /= params.base) {
		++out;
	}

	return out;
}


i64 _wh_intpos(_wh_intpos_params params) {
#ifdef WH_USE_FORTRAN
	return _wh_fortran_intpos64(params.base, params.value);
#else
	return _wh_c_intpos(params);
#endif
}

i64 _wh_intpow(_wh_intpow_params params) {
	i64 power = 1;
	
	while (params.times--) {
		power *= params.value;
	}

	return power;
}

i64 _wh_hash_simple(_wh_hash_simple_params params) {
	i64 key = -1;

	if (NULL == params.str || 0 >= params.limit) {
		goto go_error_exit;
	}

	if (0 >= params.length) {
		params.length = strlen(params.str);
	}

	for (u64 i = 0; i < params.length; i++) {
		key = (key + ((params.str[i] * 7) * (1 + i))) % params.limit;
	}

go_error_exit:
	return key;
}

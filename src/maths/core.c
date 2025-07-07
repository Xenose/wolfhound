#include<string.h>
#include<wh/maths/core.h>

#include<stdio.h>

#ifdef WH_USE_FORTRAN
extern int64_t _wh_fortran_intlog64(int64_t base, int64_t value);
extern int64_t _wh_fortran_intpow64(int64_t power, int64_t times);
#endif

i64 _wh_intlog(_wh_intlog_params params) {
#ifdef WH_USE_FORTRAN
	return _wh_fortran_intlog64(params.base, params.value);
#else
	i64 out = 0;

	if (0 == params.base) {
		params.base = 10;
	}

	while (params.value /= params.base) {
		++out;
	}

	return out;
#endif
}

i64 _wh_intpow(_wh_intpow_params params) {
	i64 power = 1;
	
	while (params.times--) {
		power *= params.value;
	}

	return power;
}

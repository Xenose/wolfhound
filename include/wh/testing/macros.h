#ifndef _wh_header_testing_macros_
#define _wh_header_testing_macros_

#include<stdio.h>

#define WH_TEST_IS_EQUAL(count_failed, count_passed, _excpected_, _result_) \
{\
	if (_excpected_ != _result_) {\
		++(count_failed);\
		printf("\t[\033[31mFAILED\033[0m] %li != %li for [ \033[33m%s\033[0m ]\n", _excpected_, _result_, #_result_);\
	} else {\
		++(count_passed);\
		printf("[\033[32mPASSED\033[0m] %li != %li for [ \033[33m%s\033[0m ]\n", _excpected_, _result_, #_result_);\
	}\
}

#endif /* _wh_header_testing_macros_ */

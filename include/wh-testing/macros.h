#ifndef _wh_header_testing_macros_
#define _wh_header_testing_macros_

#include<stdio.h>
#include<string.h>

#include<wh/common.h>

typedef struct {
	i64 passed;
	i64 failed;
} wh_utest_results_s;

#define WH_TEST_IS_EQUAL(_results_, _excpected_, _result_) \
{\
	if (_excpected_ != _result_) {\
		++(_results_->failed);\
		printf("\t[\033[31mFAILED\033[0m] %li != %li for [ \033[33m%s\033[0m ]\n", _excpected_, _result_, #_result_);\
	} else {\
		++(_results_->passed);\
		printf("[\033[32mPASSED\033[0m] %li == %li for [ \033[33m%s\033[0m ]\n", _excpected_, _result_, #_result_); \
	}\
}

#define WH_TEST_IS_EQUAL_STR(_results_, _excpected_, _result_) \
{\
	if (0 != strcmp(_excpected_, _result_)) {\
		++(_results_->failed);\
		printf("\t[\033[31mFAILED\033[0m] (%s) != (%s) for [ \033[33m%s\033[0m ] %i\n", _excpected_, _result_, #_result_, strcmp(_excpected_, _result_));\
	} else {\
		++(_results_->passed);\
		printf("[\033[32mPASSED\033[0m] %li == %li for [ \033[33m%s\033[0m ]\n", _excpected_, _result_, #_result_); \
	}\
}

#endif /* _wh_header_testing_macros_ */

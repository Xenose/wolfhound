#ifndef _wh_header_testing_unit_
#define _wh_header_testing_unit_

#include<wh/common.h>

typedef struct {
	i64 passed;
	i64 falied;
} wh_test_data_s;


#define WH_TEST_IS_EQUAL(_excpected_, _result_) \
	void _wh_test(_excpected_ == _result_, #_result_)


#define WH_TEST_IS_EQUAL_STR(_excpected_, _result_) \
	void _wh_test(strcmp(_excpected_, _result_), #_result_)

#endif /* _wh_header_testing_unite_ */

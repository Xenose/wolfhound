#ifndef _wh_header_testing_unit_
#define _wh_header_testing_unit_

#include<wh-posix/stdint.h>
#include<wh-posix/stdio.h>
#include<wh-core/c23-comp.h>

typedef struct {
    int64_t count;
} wh_unit_test_params;

typedef struct {
    const char* name;
    const char* file;
    uint64_t line;
    uint64_t passed;
    uint64_t failed;
    wh_unit_test_params params;
} wh_unit_test_s;

#define WH_TEST(_name_, ...) for (wh_unit_test_s _name_##_test = { \
            .name = #_name_, \
            .file = __FILE__, \
            .line = __LINE__, \
            .params = (wh_unit_test_params) { WH_VA_OPT(__VA_ARGS__) } \
        }; -1 < _name_##_test.params.count; \
        0 == printf("\n\tTEST REPORT [ failed : %lu, passed : %lu ]\n", _name_##_test.failed, _name_##_test.passed) ? _name_##_test.params.count-- : _name_##_test.params.count--)

#define _WH_TEST_CMP(_name_, _cmp_, _print_failure_, _print_success_) \
    wh_try { \
            if _cmp_ { \
                _print_success_ \
                ++(_name_##_test).passed; \
            } else { \
                _print_failure_ \
                ++(_name_##_test).failed; \
            } \
    } wh_catch(wh_exception_s, _ex) { \
        _print_failure_ \
        ++(_name_##_test).failed; \
    }


#define WH_TEST_STREQ(_name_, s1, s2, ...) \
    _WH_TEST_CMP( \
            _name_,  (!strcmp(s2, s1)), \
            {printf("\t[ \033[31mFAILED\033[0m ] s1 -> [ %s  ] s2 -> [ %s ] " __VA_ARGS__ "\n", s1, s2);}, \
            {printf("\t[ \033[32mPASSED\033[0m ] " __VA_ARGS__ "\n");})

#define WH_TEST_INT32EQ(_name_, i1, i2, ...) \
    _WH_TEST_CMP( \
            _name_, (i2 == i1), \
            {printf("\t[ \033[31mFAILED\033[0m ] int1 -> [ %i  ] int2 -> [ %i ] " __VA_ARGS__ "\n", i1, i2);}, \
            {printf("\t[ \033[32mPASSED\033[0m ] " __VA_ARGS__ "\n");})

#define WH_TEST_INT64EQ(_name_, i1, i2, ...) \
    _WH_TEST_CMP( \
            _name_, (i2 == i1), \
            {printf("\t[ \033[31mFAILED\033[0m ] \033[41m%s == %s [ %li :  %li ] " __VA_ARGS__ "\033[0m\n", #i1, #i2, i1, i2);}, \
            {printf("\t[ \033[32mPASSED\033[0m ] %s == %s " __VA_ARGS__ "\n", #i1, #i2);})

#endif /* _wh_header_testing_unit_ */

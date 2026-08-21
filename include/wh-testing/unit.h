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
        }; -1 < _name_##_test.params.count; _name_##_test.params.count--)

#define WH_TEST_STREQ(_name_, s1, s2, ...) \
    wh_try { \
            if (!strcmp(s2, s1)) { \
                printf("\t[ \033[32mPASSED\033[0m ] " __VA_ARGS__ "\n"); \
                ++_name_.passed; \
            } else { \
                printf("\t[ \033[31mFAILED\033[0m ] s1 -> [ %s  ] s2 -> [ %s ] " __VA_ARGS__ "\n", s1, s2); \
                ++_name_.failed; \
            } \
    } wh_catch(wh_exception_s, _ex) { \
    }

#define WH_TEST_REPORT(_name_) \
    printf("\n\tTEST REPORT [ failed : %lu, passed : %lu ]\n", _name_.failed, _name_.passed)


#endif /* _wh_header_testing_unit_ */

#include<wh-testing/unit.h>
#include<wh/maths/core.h>

i64 test_intpos(wh_unit_test_s* info) {
    // TODO add other bases as well.
    for (long i = 0, d = 1; d < INT_MAX; d *= 10, i++) {
        WH_TEST_INT64EQ(info, wh_intpos(d), i);
    }

    return 0;
}

i64 init(wh_unit_test_s* info) {
    test_intpos(info);
    return 0;
}

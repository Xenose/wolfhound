#include<wh-testing/unit.h>
#include<wh/maths/core.h>

static i64 test_simple(wh_unit_test_s* info) {
    WH_TEST_INT64EQ(info, wh_intpos(0), 0L);
    WH_TEST_INT64EQ(info, wh_intpos(6), 0L);
    WH_TEST_INT64EQ(info, wh_intpos(9), 0L);

    WH_TEST_INT64EQ(info, wh_intpos(10), 1L);
    WH_TEST_INT64EQ(info, wh_intpos(16), 1L);
    WH_TEST_INT64EQ(info, wh_intpos(19), 1L);

    return 0;
}

i64 init(wh_unit_test_s* info) {
    test_simple(info);
    return 0;
}

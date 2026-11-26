#include<wh-testing/unit.h>
#include<wh-sys/data/dynamic_array.h>
#include<wh-sys/debug/logger.h>

i64 check_enum_order(wh_unit_test_s* info) {
    WH_TEST_INT64EQ(info, 0L, (i64)WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF);
    WH_TEST_INT64EQ(info, 1L, (i64)WH_STRUCT_TYPE_DYNAMIC_ARRAY_SYS - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF);
    WH_TEST_INT64EQ(info, 2L, (i64)WH_STRUCT_TYPE_DYNAMIC_ARRAY_STD - WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF);

    return 0;
}

i64 simple_darray(wh_unit_test_s* info, wh_darray_s* array) {
    wh_darray_set(array, 0, WH_INT(10));
    wh_darray_set(array, 4, WH_INT(12));

    WH_TEST_INT64EQ(info, 10L, (i64)*((int*)wh_darray_get(array, 0)));
    WH_TEST_INT64EQ(info, 12L, (i64)*((int*)wh_darray_get(array, 4)));
    return 0;
}

i64 init(wh_unit_test_s* info) {
    wh_darray_s array = { 0 };
    wh_log_set_level(WH_LOG_LEVEL_ALL, 1);
   
    // Checking enum order
    WH_TEST(info, check_enum_order(info));
   
    // Start of the real tests
    wh_darray_init(WH_STRUCT_TYPE_DYNAMIC_ARRAY_STD, &array, sizeof(int), 100);
    WH_TEST(info, simple_darray(info, &array));

    return 0;
}

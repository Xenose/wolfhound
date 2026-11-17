#include<wh-testing/unit.h>
#include<wh-sys/data/dynamic_array.h>
#include<wh-sys/debug/logger.h>


i64 simple_darray(wh_unit_test_s* info) {
    return 0;
}

i64 init(wh_unit_test_s* info) {
    wh_darray_s array = { 0 };
    wh_log_set_level(WH_LOG_LEVEL_ALL, 0);
    
    wh_darray_init(WH_STRUCT_TYPE_DYNAMIC_ARRAY_WOLF, &array, sizeof(int), 100);

    WH_TEST(info, simple_darray(info));
    return 0;
}

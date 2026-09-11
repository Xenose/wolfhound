#include<wh-testing/unit.h>
#include<wh-sys/data/hashmap.h>
#include<wh-sys/debug/logger.h>

i64 test_insert(wh_unit_test_s* info, wh_hashmap_s* hs) {
    wh_hashmap_insert(hs, "hello", WH_INT(64));

    WH_TEST_INT64EQ(info, 64L, (long)*(int*)wh_hashmap_get(hs, "hello"));

    return 0;
}


i64 init(wh_unit_test_s* info) {
    // Log levels are noisy for unit testing.
    wh_log_set_level(WH_LOG_LEVEL_EMERGENCY,    0);
    wh_log_set_level(WH_LOG_LEVEL_ALERT,        0);
    wh_log_set_level(WH_LOG_LEVEL_CRITICAL,     0);
    wh_log_set_level(WH_LOG_LEVEL_ERROR,        0);
    wh_log_set_level(WH_LOG_LEVEL_WARNING,      0);
    wh_log_set_level(WH_LOG_LEVEL_NOTICE,       0);
    wh_log_set_level(WH_LOG_LEVEL_INFO,         0);
    wh_log_set_level(WH_LOG_LEVEL_DEBUG,        0);


    wh_hashmap_s hs = wh_hashmap_init_mmap_lazy(sizeof(int), 1);

    test_insert(info, &hs);

    return 0; 
}

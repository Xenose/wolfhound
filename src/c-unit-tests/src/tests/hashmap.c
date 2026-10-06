#include<wh-testing/unit.h>
#include<wh-sys/data/hashmap.h>
#include<wh-sys/debug/logger.h>

i64 test_order(wh_unit_test_s* info, wh_hashmap_s* hs) {
    WH_TEST_INT64EQ(info, 0L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 1L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 2L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_STD - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);

    WH_TEST_INT64EQ(info, 3L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I64_WOLF - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 4L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I64_SYS - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 5L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I64_STD - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);

    WH_TEST_INT64EQ(info, 6L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I32_WOLF - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 7L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I32_SYS - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 8L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_I32_STD - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);

    WH_TEST_INT64EQ(info, 9L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_WOLF - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 10L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    WH_TEST_INT64EQ(info, 11L, (i64)WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_STD - WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_WOLF);
    return 0;
}

i64 test_insert(wh_unit_test_s* info, wh_hashmap_s* hs) {
    wh_hashmap_insert(hs, "hello", WH_INT(64));
    WH_TEST_INT64EQ(info, 64L, (long)*(int*)wh_hashmap_get(hs, "hello"));
    
    wh_hashmap_insert(hs, "hello2", WH_INT(63));
    WH_TEST_INT64EQ(info, 63L, (long)*(int*)wh_hashmap_get(hs, "hello2"));

    wh_hashmap_insert(hs, "hello3", WH_INT(62));
    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello3"));

    wh_hashmap_insert(hs, "hello4", WH_INT(62));
    wh_hashmap_insert(hs, "hello5", WH_INT(61));
    wh_hashmap_insert(hs, "hello6", WH_INT(60));
    wh_hashmap_insert(hs, "hello7", WH_INT(59));
    wh_hashmap_insert(hs, "hello8", WH_INT(58));
    wh_hashmap_insert(hs, "hello9", WH_INT(57));

    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello4"));
    WH_TEST_INT64EQ(info, 61L, (long)*(int*)wh_hashmap_get(hs, "hello5"));
    WH_TEST_INT64EQ(info, 60L, (long)*(int*)wh_hashmap_get(hs, "hello6"));
    WH_TEST_INT64EQ(info, 59L, (long)*(int*)wh_hashmap_get(hs, "hello7"));
    WH_TEST_INT64EQ(info, 58L, (long)*(int*)wh_hashmap_get(hs, "hello8"));
    WH_TEST_INT64EQ(info, 57L, (long)*(int*)wh_hashmap_get(hs, "hello9"));

    wh_hashmap_insert(hs, "hello14", WH_INT(62));
    wh_hashmap_insert(hs, "hello15", WH_INT(61));
    wh_hashmap_insert(hs, "hello16", WH_INT(60));
    wh_hashmap_insert(hs, "hello17", WH_INT(59));
    wh_hashmap_insert(hs, "hello18", WH_INT(58));
    wh_hashmap_insert(hs, "hello19", WH_INT(57));

    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello14"));
    WH_TEST_INT64EQ(info, 61L, (long)*(int*)wh_hashmap_get(hs, "hello15"));
    WH_TEST_INT64EQ(info, 60L, (long)*(int*)wh_hashmap_get(hs, "hello16"));
    WH_TEST_INT64EQ(info, 59L, (long)*(int*)wh_hashmap_get(hs, "hello17"));
    WH_TEST_INT64EQ(info, 58L, (long)*(int*)wh_hashmap_get(hs, "hello18"));
    WH_TEST_INT64EQ(info, 57L, (long)*(int*)wh_hashmap_get(hs, "hello19"));

    wh_hashmap_insert(hs, "hello24", WH_INT(62));
    wh_hashmap_insert(hs, "hello25", WH_INT(61));
    wh_hashmap_insert(hs, "hello26", WH_INT(60));
    wh_hashmap_insert(hs, "hello27", WH_INT(59));
    wh_hashmap_insert(hs, "hello28", WH_INT(58));
    wh_hashmap_insert(hs, "hello29", WH_INT(57));

    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello24"));
    WH_TEST_INT64EQ(info, 61L, (long)*(int*)wh_hashmap_get(hs, "hello25"));
    WH_TEST_INT64EQ(info, 60L, (long)*(int*)wh_hashmap_get(hs, "hello26"));
    WH_TEST_INT64EQ(info, 59L, (long)*(int*)wh_hashmap_get(hs, "hello27"));
    WH_TEST_INT64EQ(info, 58L, (long)*(int*)wh_hashmap_get(hs, "hello28"));
    WH_TEST_INT64EQ(info, 57L, (long)*(int*)wh_hashmap_get(hs, "hello29"));

    wh_hashmap_insert(hs, "hello34", WH_INT(62));
    wh_hashmap_insert(hs, "hello35", WH_INT(61));
    wh_hashmap_insert(hs, "hello36", WH_INT(60));
    wh_hashmap_insert(hs, "hello37", WH_INT(59));
    wh_hashmap_insert(hs, "hello38", WH_INT(58));
    wh_hashmap_insert(hs, "hello39", WH_INT(57));

    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello34"));
    WH_TEST_INT64EQ(info, 61L, (long)*(int*)wh_hashmap_get(hs, "hello35"));
    WH_TEST_INT64EQ(info, 60L, (long)*(int*)wh_hashmap_get(hs, "hello36"));
    WH_TEST_INT64EQ(info, 59L, (long)*(int*)wh_hashmap_get(hs, "hello37"));
    WH_TEST_INT64EQ(info, 58L, (long)*(int*)wh_hashmap_get(hs, "hello38"));
    WH_TEST_INT64EQ(info, 57L, (long)*(int*)wh_hashmap_get(hs, "hello39"));

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

    test_order(info, &hs);
    test_insert(info, &hs);

    return 0; 
}

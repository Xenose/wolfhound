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

    // Adding random stuff
    wh_hashmap_insert(hs, "AAhello24", WH_INT(2));
    wh_hashmap_insert(hs, "AAhello25", WH_INT(1));
    wh_hashmap_insert(hs, "AAhello26", WH_INT(0));
    wh_hashmap_insert(hs, "AAhello27", WH_INT(9));
    wh_hashmap_insert(hs, "AAhello28", WH_INT(8));
    wh_hashmap_insert(hs, "AAhello29", WH_INT(7));
    wh_hashmap_insert(hs, "AAhello34", WH_INT(2));
    wh_hashmap_insert(hs, "AAhello35", WH_INT(1));
    wh_hashmap_insert(hs, "AAhello36", WH_INT(0));
    wh_hashmap_insert(hs, "AAhello37", WH_INT(9));
    wh_hashmap_insert(hs, "AAhello38", WH_INT(8));
    wh_hashmap_insert(hs, "AAhello39", WH_INT(7));
    wh_hashmap_insert(hs, "bAhello24", WH_INT(2));
    wh_hashmap_insert(hs, "bAhello25", WH_INT(1));
    wh_hashmap_insert(hs, "bAhello26", WH_INT(0));
    wh_hashmap_insert(hs, "bAhello27", WH_INT(9));
    wh_hashmap_insert(hs, "bAhello28", WH_INT(8));
    wh_hashmap_insert(hs, "bAhello29", WH_INT(7));
    wh_hashmap_insert(hs, "bAhello34", WH_INT(2));
    wh_hashmap_insert(hs, "bAhello35", WH_INT(1));
    wh_hashmap_insert(hs, "bAhello36", WH_INT(0));
    wh_hashmap_insert(hs, "bAhello37", WH_INT(9));
    wh_hashmap_insert(hs, "bAhello38", WH_INT(8));
    wh_hashmap_insert(hs, "bAhello39", WH_INT(7));
    wh_hashmap_insert(hs, "AAhdddaosdksokello24", WH_INT(2));
    wh_hashmap_insert(hs, "AAhdddaosdksokello25", WH_INT(1));
    wh_hashmap_insert(hs, "AAhdddaosdksokello26", WH_INT(0));
    wh_hashmap_insert(hs, "AAhdddaosdksokello27", WH_INT(9));
    wh_hashmap_insert(hs, "AAhdddaosdksokello28", WH_INT(8));
    wh_hashmap_insert(hs, "AAhdddaosdksokello29", WH_INT(7));
    wh_hashmap_insert(hs, "AAhdddaosdksokello34", WH_INT(2));
    wh_hashmap_insert(hs, "AAhdddaosdksokello35", WH_INT(1));
    wh_hashmap_insert(hs, "AAhdddaosdksokello36", WH_INT(0));
    wh_hashmap_insert(hs, "AAhdddaosdksokello37", WH_INT(9));
    wh_hashmap_insert(hs, "AAhdddaosdksokello38", WH_INT(8));
    wh_hashmap_insert(hs, "AAhdddaosdksokello39", WH_INT(7));
    wh_hashmap_insert(hs, "bAhdddaosdksokello24", WH_INT(2));
    wh_hashmap_insert(hs, "bAhdddaosdksokello25", WH_INT(1));
    wh_hashmap_insert(hs, "bAhdddaosdksokello26", WH_INT(0));
    wh_hashmap_insert(hs, "bAhdddaosdksokello27", WH_INT(9));
    wh_hashmap_insert(hs, "bAhdddaosdksokello28", WH_INT(8));
    wh_hashmap_insert(hs, "bAhdddaosdksokello29", WH_INT(7));
    wh_hashmap_insert(hs, "bAhdddaosdksokello34", WH_INT(2));
    wh_hashmap_insert(hs, "bAhdddaosdksokello35", WH_INT(1));
    wh_hashmap_insert(hs, "bAhdddaosdksokello36", WH_INT(0));
    wh_hashmap_insert(hs, "bAhdddaosdksokello37", WH_INT(9));
    wh_hashmap_insert(hs, "bAhdddaosdksokello38", WH_INT(8));
    wh_hashmap_insert(hs, "bAhdddaosdksokello39", WH_INT(7));

    // Testing older entries
    WH_TEST_INT64EQ(info, 63L, (long)*(int*)wh_hashmap_get(hs, "hello2"));
    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello3"));
    WH_TEST_INT64EQ(info, 62L, (long)*(int*)wh_hashmap_get(hs, "hello4"));
    WH_TEST_INT64EQ(info, 61L, (long)*(int*)wh_hashmap_get(hs, "hello5"));
    WH_TEST_INT64EQ(info, 60L, (long)*(int*)wh_hashmap_get(hs, "hello6"));
    WH_TEST_INT64EQ(info, 59L, (long)*(int*)wh_hashmap_get(hs, "hello7"));
    WH_TEST_INT64EQ(info, 58L, (long)*(int*)wh_hashmap_get(hs, "hello8"));
    WH_TEST_INT64EQ(info, 57L, (long)*(int*)wh_hashmap_get(hs, "hello9"));
    WH_TEST_INT64EQ(info, 2L,  (long)*(int*)wh_hashmap_get(hs, "AAhello24"));

    return 0;
}

i64 test_keys(wh_unit_test_s* info, wh_hashmap_s* hs) {
    char* tmp = nullptr;

    tmp = wh_hashmap_get_key(hs, "hello39");

    printf("tmp: %p -> str: %p", tmp, "hello39");
    WH_TEST_STREQ(info, tmp, "hello39");

    return 0;
}

i64 test_delete(wh_unit_test_s* info, wh_hashmap_s* hs) {
    wh_hashmap_delete(hs, "bAhdddaosdksokello39");
    
    WH_TEST_INT64EQ(info, 2L,  (long)*(int*)wh_hashmap_get(hs, "bAhdddaosdksokello39"));

    return 0;
}

i64 init(wh_unit_test_s* info) {
    // Log levels are noisy for unit testing.
    // DEBUGGING: set to 1 and normally should be 0.
    wh_log_set_level(WH_LOG_LEVEL_ALL, 1);

    wh_hashmap_s hs = wh_hashmap_init_mmap_lazy(sizeof(int), 1);

    WH_TEST(info, test_order(info, &hs));
    WH_TEST(info, test_insert(info, &hs));
    WH_TEST(info, test_keys(info, &hs));
    WH_TEST(info, test_delete(info, &hs));

    return 0; 
}

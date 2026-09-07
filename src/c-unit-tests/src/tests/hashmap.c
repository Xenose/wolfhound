#include<wh-testing/unit.h>
#include<wh-sys/data/hashmap.h>

i64 test_insert(wh_unit_test_s* info, wh_hashmap_s* hs) {
    wh_hashmap_insert(hs, "hello", WH_INT(64));

    WH_TEST_INT64EQ(info, 64L, (long)*(int*)wh_hashmap_get(hs, "hello"));

    return 0;
}


i64 init(wh_unit_test_s* info) {
    wh_hashmap_s hs = wh_hashmap_init_mmap_lazy(sizeof(int), 1);

    test_insert(info, &hs);

    return 0; 
}

#include<wh-testing/unit.h>
#include<wh-sys/data/list.h>
#include<wh-sys/debug/logger.h>


i64 simple_dll(wh_unit_test_s* info) {
    wh_list_s l = wh_dlist_init_stdlib(sizeof(int));

    wh_list_insert(&l, 0, WH_INT(20));
    wh_list_insert(&l, 0, WH_INT(20));
    wh_list_insert(&l, 0, WH_INT(5));
    wh_list_insert(&l, 3, WH_INT(40));
    wh_list_insert(&l, 1, WH_INT(40));
    wh_list_insert(&l, 1, WH_INT(50));
    wh_list_insert(&l, 3, WH_INT(150));
    wh_list_insert(&l, 2, WH_INT(10));

    wh_list_delete(&l, 3);

    WH_TEST_INT32EQ(info, 5,  (*(int*)wh_list_get(int, &l, 0)));
    WH_TEST_INT32EQ(info, 50, (*(int*)wh_list_get(int, &l, 1)));
    WH_TEST_INT32EQ(info, 10, (*(int*)wh_list_get(int, &l, 2)));

    return 0;
}

i64 init(wh_unit_test_s* info) {
    wh_log_set_level(WH_LOG_LEVEL_ALL, 0);

    simple_dll(info);
    return 0;
}

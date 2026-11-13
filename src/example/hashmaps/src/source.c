#include<wh-sys/data/hashmap.h>
#include<wh-core/debug/logger.h>
#include<wh/debug/signalar.h>
#include<wh/debug/benchmark.h>

void hash_foreach(wh_hashmap_foreach_s* value) {
    wh_debug(("--> %i"), *((int*)value->ptr));
}

int main(int arc, char* const* arv) {
    wh_benchmark_s bench = { 0 };
    wh_hashmap_s l = wh_hashmap_init_mmap_lazy(sizeof(int));
    wh_hashmap_s p = wh_hashmap_init_mmap_lazy_ptr(sizeof(int));

    wh_signalar_init(arv[0]);
    //wh_log_set_level(WH_LOG_LEVEL_DEBUG, 1);

    wh_debug(("Hello!"));
    wh_hashmap_insert(&l, "test", WH_INT(10));

    wh_benchmark(&bench, 1) {
        // TODO fix items with the same id
        // wh_hashmap_insert(&l, "test", WH_INT(10));
        wh_hashmap_insert(&l, "test2", WH_INT(15));
        wh_debug(("1 : %i\n\n"), *(int*)wh_hashmap_get(&l, "test"));

        wh_hashmap_insert(&l, "test3", WH_INT(30));
        wh_hashmap_insert(&l, "test4", WH_INT(35));
        wh_hashmap_insert(&l, "test5", WH_INT(15));
        wh_hashmap_insert(&l, "test6", WH_INT(30));
        wh_hashmap_insert(&l, "test7", WH_INT(35));
        wh_hashmap_insert(&l, "test8", WH_INT(35));
        wh_hashmap_insert(&l, "test9", WH_INT(35));
        wh_hashmap_insert(&l, "test10", WH_INT(35));
        wh_hashmap_insert(&l, "test11", WH_INT(35));
        wh_hashmap_insert(&l, "test12", WH_INT(35));
        wh_hashmap_insert(&l, "test13", WH_INT(35));
        wh_hashmap_insert(&l, "test14", WH_INT(35));
        wh_hashmap_insert(&l, "test15", WH_INT(35));
        wh_hashmap_insert(&l, "test16", WH_INT(35));
        wh_hashmap_insert(&l, "test17", WH_INT(35));
        wh_hashmap_insert(&l, "test18", WH_INT(35));
        wh_hashmap_insert(&l, "test19", WH_INT(35));
        wh_hashmap_insert(&l, "test20", WH_INT(35));

        wh_debug(("1 : %i"), *(int*)wh_hashmap_get(&l, "test"));
        wh_debug(("2 : %i"), *(int*)wh_hashmap_get(&l, "test2"));
        wh_debug(("3 : %i"), *(int*)wh_hashmap_get(&l, "test3"));
        wh_debug(("4 : %i"), *(int*)wh_hashmap_get(&l, "test4"));
        wh_debug(("5 : %i"), *(int*)wh_hashmap_get(&l, "test5"));
        wh_debug(("6 : %i"), *(int*)wh_hashmap_get(&l, "test6"));
        wh_debug(("7 : %i"), *(int*)wh_hashmap_get(&l, "test7"));
        wh_debug(("8 : %i"), *(int*)wh_hashmap_get(&l, "test8"));
        wh_debug(("9 : %i"), *(int*)wh_hashmap_get(&l, "test9"));
        wh_debug(("10: %i"), *(int*)wh_hashmap_get(&l, "test10"));
        wh_debug(("11: %i"), *(int*)wh_hashmap_get(&l, "test11"));
        wh_debug(("12: %i"), *(int*)wh_hashmap_get(&l, "test12"));
        wh_debug(("13: %i"), *(int*)wh_hashmap_get(&l, "test13"));
        wh_debug(("14: %i"), *(int*)wh_hashmap_get(&l, "test14"));
        wh_debug(("15: %i"), *(int*)wh_hashmap_get(&l, "test15"));
        wh_debug(("16: %i"), *(int*)wh_hashmap_get(&l, "test16"));
        wh_debug(("17: %i"), *(int*)wh_hashmap_get(&l, "test17"));
        wh_debug(("18: %i"), *(int*)wh_hashmap_get(&l, "test18"));
        wh_debug(("19: %i"), *(int*)wh_hashmap_get(&l, "test19"));
        wh_debug(("20: %i"), *(int*)wh_hashmap_get(&l, "test20"));
    }

    wh_hashmap_insert(&p, WH_INT(100), WH_INT(10));
    wh_hashmap_insert(&p, WH_INT(101), WH_INT(12));

    wh_print(("\nTime -> %is %ins\n", 2), bench.delta.time.tv_sec, bench.delta.time.tv_nsec);
    _wh_hashmap_foreach(&l, &hash_foreach);
    _wh_hashmap_foreach(&p, &hash_foreach);
    return 0;
}

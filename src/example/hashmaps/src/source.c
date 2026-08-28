#include<wh-sys/data/hashmap.h>
#include<wh/debug/logger.h>
#include<wh/debug/signalar.h>
#include<wh/debug/benchmark.h>

void hash_foreach(void* value) {
    wh_log_debug(("--> %i"), *((int*)value));
}

int main(int arc, char* const* arv) {
    wh_benchmark_s bench = { 0 };
    wh_hashmap_s l = wh_hashmap_init_mmap_lazy(sizeof(int));
    wh_hashmap_s p = wh_hashmap_init_mmap_lazy_ptr(sizeof(int));

    wh_signalar_init(arv[0]);
    //wh_log_set_level(WH_LOG_LEVEL_DEBUG, 1);

    wh_log_debug(("Hello!"));
    wh_hashmap_insert(&l, "test", WH_INT(10));

    wh_benchmark(&bench, 1) {
        // TODO fix items with the same id
        // wh_hashmap_insert(&l, "test", WH_INT(10));
        wh_hashmap_insert(&l, "test2", WH_INT(15));
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

        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test"));
        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test2"));
        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test3"));
        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test4"));
        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test5"));
        wh_log_debug(("%i"), *(int*)wh_hashmap_get(&l, "test6"));
        wh_log_debug(("%i\n"), *(int*)wh_hashmap_get(&l, "test7"));
    }

    wh_hashmap_insert(&p, WH_INT(100), WH_INT(10));
    wh_hashmap_insert(&p, WH_INT(101), WH_INT(12));

    wh_print(("\nTime -> %is %ins\n", 2), bench.delta.time.tv_sec, bench.delta.time.tv_nsec);
    _wh_hashmap_foreach(&l, &hash_foreach);

    wh_log_info(("Ptr --------\n"));
    _wh_hashmap_foreach(&p, &hash_foreach);
    return 0;
}

#include<wh-testing/unit.h>
#include<wh-sys/memory.h>
#include<wh-sys/debug/logger.h>

#define HEAP_SIZE 4096
#define PTR_COUNT 256

i64 test_memory_reuse(wh_unit_test_s* info, wh_heap_header_s* heap) {
    void* p1 = nullptr;
    void* p2 = nullptr;
    void* p3 = nullptr;

    p1 = wh_alloc(heap, 64, &p1);
    wh_free(heap, p1, &p1);

    p2 = wh_alloc(heap, 64, &p2);

    WH_TEST_INT64EQ(info, (int64_t)p1, (int64_t)p2);
    wh_free(heap, p2, &p2);
    
    p3 = wh_alloc(heap, 64, &p3);
    WH_TEST_INT64EQ(info, (int64_t)p3, (int64_t)p2);
    wh_free(heap, p3, &p3);

    return 0;
}

i64 test_memory_large_allocation(wh_unit_test_s* info, wh_heap_header_s* heap) {
    void* ptrs[PTR_COUNT] = { nullptr };

    for (uint64_t i = 0; i < PTR_COUNT; i++) {
        ptrs[i] = wh_alloc(heap, 64, &ptrs[i]);
    }

    _wh_mem_scan();
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

    // Need a heap to test on.
    wh_heap_header_s* heap = wh_heap_init("main", HEAP_SIZE);

    // Checking of the heap was allocated.
    WH_TEST_INT64EQ(info, (int64_t)!heap, (int64_t)NULL);

    test_memory_reuse(info, heap);
    test_memory_large_allocation(info, heap);

    return 0;
}

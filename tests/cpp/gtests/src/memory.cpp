#include<wh/memory.h>
#include<wh/debug/exceptions.h>
#include<wh/testing/macros.h>
#include<wh/debug/logger.h>

#include<gtest/gtest.h>

void _memory_test(wh_heap_header_s* heap, u64 bytes) {
	void* p1 = nullptr;
	void* p2 = nullptr;

	_wh_mem_free_params params_free;
	_wh_mem_alloc_params params_alloc;

	params_alloc = {
		heap,
		bytes,
		&p1
	};

	p1 = _wh_alloc(params_alloc);

	params_free = {
		heap, p1, &p1
	};

	_wh_free(params_free);

	params_alloc = {
		heap,
		bytes,
		&p2
	};

	p2 = _wh_alloc(params_alloc);

	params_free = {
		heap, p2, &p2
	};

	_wh_free(params_free);

	EXPECT_EQ((u64)p1, (u64)p2);
}

/*void _memory_test_leak(wh_heap_header_s* heap, u64 bytes) {
	void* p1 = nullptr;

	// We don't need error logs when we know there is a leak
	wh_log_set_level(WH_LOG_LEVEL_ERROR, 0);

	p1 = wh_alloc(heap, bytes, &p1);
	EXPECT_EQ(1L, _wh_mem_scan());
	EXPECT_EQ(0L, _wh_mem_scan());

	// But we want logs after this test.
	wh_log_set_level(WH_LOG_LEVEL_ERROR, 1);
}*/

TEST(memory, general) {
	wh_heap_header_s* heap = wh_heap_init("main_heap", WH_1MB, nullptr, WH_STRUCT_TYPE_HEAP_ARENA);

	_memory_test(heap, 1024);
	_memory_test(heap, 32);
	_memory_test(heap, 72);
	_memory_test(heap, 72000);
	//_memory_test_leak(heap, 72);

	_wh_mem_scan();
}

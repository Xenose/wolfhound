#include<wh-sys/memory.h>
#include<wh-testing/exceptions.h>
#include<wh-testing/macros.h>
#include<wh/debug/logger.h>

#include<wh_tests/memory.h>

void _memory_test(i64* failed, i64* passed, wh_heap_header_s* heap, u64 bytes) {
	void* p1 = nullptr;
	void* p2 = nullptr;

	p1 = wh_alloc(heap, bytes, &p1);
	wh_free(heap, p1, &p1);

	p2 = wh_alloc(heap, bytes, &p2);
	wh_free(heap, p2, &p2);

	WH_TEST_IS_EQUAL(*failed, *passed, (u64)p1, (u64)p2);
}

void _memory_test_leak(i64* failed, i64* passed, wh_heap_header_s* heap, u64 bytes) {
	void* p1 = nullptr;

	// We don't need error logs when we know there is a leak
	wh_log_set_level(WH_LOG_LEVEL_ERROR, 0);

	p1 = wh_alloc(heap, bytes, &p1);
	WH_TEST_IS_EQUAL(*failed, *passed, 1L, _wh_mem_scan());
	WH_TEST_IS_EQUAL(*failed, *passed, 0L, _wh_mem_scan());

	// But we want logs after this test.
	wh_log_set_level(WH_LOG_LEVEL_ERROR, 1);
}

i64 testing_memory(i64* failed, i64* passed) {
	wh_heap_header_s* heap = wh_heap_init("main_heap", WH_1MB, nullptr, WH_STRUCT_TYPE_HEAP_ARENA);

	wh_try {
		_memory_test(failed, passed, heap, 1024);
		_memory_test(failed, passed, heap, 32);
		_memory_test(failed, passed, heap, 72);
		_memory_test(failed, passed, heap, 72000);
	
		_memory_test_leak(failed, passed, heap, 72);
	} wh_catch(exp) {
		switch (exp.error) {
			case WH_EXCEPTION_SIGSEGV:
				printf("unsafe to continue...\n");
				return exp.error;
		}
	}

	_wh_mem_scan();
	return 0;
}

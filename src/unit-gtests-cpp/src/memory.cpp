#include<wh/debug/exceptions.h>
#include<wh-testing/macros.h>
#include<wh-sys/debug/logger.h>

#include<wh-sys/memory.h>
#include<wh-cpp/memory.hpp>

#include<gtest/gtest.h>

class memory_test_c : public ::testing::Test {
protected:
	void SetUp() {
		_wh_heap_init_params params = {
			"main",
			WH_1MB
		};

		_wh_heap_init(params);
	}
};


TEST_F(memory_test_c, general) {
	float* f = wh::memory_c("main").alloc<float>(64, &f);
	EXPECT_NE(nullptr, f);

	wh::memory_c("main").free(f);

	EXPECT_EQ(0, _wh_mem_scan());
}

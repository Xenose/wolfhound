#include<wh/debug/exceptions.h>
#include<wh/testing/macros.h>
#include<wh/debug/logger.h>

#include<wh/memory.h>
#include<wh/cpp/memory.hpp>

#include<gtest/gtest.h>

TEST(memory, general) {
	_wh_heap_init_params params = {
		"main",
		WH_1MB
	};

	_wh_heap_init(params);
	float* f = wh::memory("main").alloc<float>(64, &f);

	EXPECT_NE(nullptr, f);
}

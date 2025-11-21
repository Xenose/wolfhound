#include<math.h>
#include<string>
#include<gtest/gtest.h>

#include<wh/cpp/maths/core.hpp>

/*
TEST(maths, abs) {
	// TODO :: work around the _Generic issue with C++
	for (i64 i = -1'000'000; i < 1'000'000; i++) {
		//EXPECT_EQ(abs(i), wh_abs(i));
	}
}
*/

TEST(maths, hash) {
	EXPECT_EQ(18L, wh::maths::hash_simple("hello", 100));
	EXPECT_EQ(318L, wh::maths::hash_simple("hello", 1000));
	EXPECT_EQ(1318L, wh::maths::hash_simple("hello", 10000));
	
	EXPECT_EQ(27L, wh::maths::hash_simple("h", 100));
	EXPECT_EQ(727L, wh::maths::hash_simple("h", 1000));
	
	EXPECT_EQ(-1L, wh::maths::hash_simple(nullptr, 1000, 0));
}

TEST(math, intpos) {
	for (int i = 1; i < 1'000'000; i += 3) {
		EXPECT_EQ(std::to_string(i).length() - 1, wh::maths::intpos(i, 10));
	}
}

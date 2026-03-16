#include<string>
#include<gtest/gtest.h>

#include<wh-cpp/maths/hash.hpp>

typedef struct {
	u64 hash;
	std::string v;
} hash_pair_s;

TEST(maths, xxHash32) {
	hash_pair_s pairs[] = {
		{ 0x02CC5D05, "" },
		{ 0x550D7456, "a" },
		{ 0x32D153FF, "abc" },
		{ 0x7C948494, "message digest" },
		{ 0x63A14D5F, "abcdefghijklmnopqrstuvwxyz" },
	};

	for (auto p : pairs) {
		EXPECT_EQ(p.hash, wh::maths::hash::xx32((wh_buffer_s){(void*)p.v.c_str(), p.v.length()}));
	}
}

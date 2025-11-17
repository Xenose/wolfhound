#include <gtest/gtest.h>

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	// Optional: filter tests via command line arguments
	// ::testing::GTEST_FLAG(filter) = "MyTestSuite.*";

	return RUN_ALL_TESTS();
}

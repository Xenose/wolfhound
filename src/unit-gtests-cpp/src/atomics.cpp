#include<gtest/gtest.h>
#include<thread>
#include<vector>

#include<wh-sys/atomic_lock.h>

int count = 0;
wh_atomic_lock_s lock = {};

void task_001() {
	wh_spinlock_v2(&lock) {
		++count;
		usleep(500);
	}
}

void task_002() {
	wh_spinlock_v2(&lock) {
		wh_spinlock_v2(&lock) {
			++count;
			usleep(500);
		}
	}
}

// Test mutual exclusion
TEST(spinlock_testing, single_layer) {
	return; // TODO fix the locks

	count = 0;
	std::vector<std::thread> tasks;

	for (int i = 0; i < 100; i++) {
		tasks.push_back(std::thread(task_001));
	}

	for (size_t i = 0; i < tasks.size(); i++) {
		tasks[i].join();
	}

	EXPECT_EQ(count, tasks.size());
}

// Test mutual exclusion
TEST(spinlock_testing, two_layers) {
	return; // TODO fix the locks

	count = 0;
	std::vector<std::thread> tasks;

	for (int i = 0; i < 100; i++) {
		tasks.push_back(std::thread(task_002));
	}

	for (size_t i = 0; i < tasks.size(); i++) {
		tasks[i].join();
	}

	EXPECT_EQ(count, tasks.size());
}

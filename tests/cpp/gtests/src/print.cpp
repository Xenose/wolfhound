#include<stdarg.h>
#include<stdlib.h>

#include<string>

#include<wh/print.h>
#include<wh/debug/exceptions.h>
#include<wh/debug/benchmark.h>
#include<wh/testing/macros.h>

#include<gtest/gtest.h>

// Wrapper for testing string comparisons
void _testing_print(const char* result, const char* format, ...) {
	va_list args;
	char buffer[8096] = { 0 };
	_wh_print_params params = {
		format, 
		1, 
		buffer, 
		8095, 
		0, 
		WH_PRINT_NO_FLUSH
	};

	va_start(args, format);

	_wh_print_va(params, args);
	EXPECT_STREQ(result, buffer);

	va_end(args);
}

TEST(print, overall_tests) {
	// Simple tests
	_testing_print("%NULL%", nullptr);

	_testing_print("%$", "%%$$");
	_testing_print("Hello", "Hello");
	_testing_print("Hello World!", "Hello World!");

	// Integer testing
	_testing_print("--> 10", "--> %i", 10);
	_testing_print("--> 100", "--> %i", 100);
	_testing_print("--> 1000", "--> %i", 1000);
	_testing_print("--> 10000", "--> %i", 10000);

	// Strings...
	_testing_print("HELLO WORLD!", "%#s", "Hello World!");
	_testing_print("He", "%.2s", "Hello World!");

	// Formatted string
	_testing_print("Hello World!", "Hello $f!", "%s", "World");
	_testing_print("Hello World!", "Hello $f!", "$f", "%s", "World");
	_testing_print("Hello World!", "Hello $f!", "$f", "$f", "%s", "World");

	// Would this even happen?
	_testing_print("Hello World 10!", "Hello $f!", "$f %d", "$f", "%s", "World", 10);
	_testing_print("Hello  10!", "Hello $f!", "$f %d", "$f", nullptr, 10);
}

TEST(print, integer_tests) {
	for (int i = -1000000; i < 100000; i++) {
		_testing_print(("--> " + std::to_string(i)).c_str(), "--> %i", i);
	}
}

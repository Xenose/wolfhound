#include<stdarg.h>
#include<wh/print.h>
#include<wh/testing/macros.h>

void _testing_print(i64* failed, i64* passed, char* result, char* format, ...) {
	char buffer[8096] = { 0 };

	va_list args;
	va_start(args, format);

	wh_print_va((format, .buffer = buffer, .buffer_length = 8095, .flags = WH_PRINT_NO_FLUSH), args);
	WH_TEST_IS_EQUAL_STR(*failed, *passed, result, buffer);

	va_end(args);
}

void testing_print(i64* failed, i64* passed) {
	// Simple tests
	_testing_print(failed, passed, "%NULL%", nullptr);

	_testing_print(failed, passed, "%$", "%%$$");
	_testing_print(failed, passed, "Hello", "Hello");
	_testing_print(failed, passed, "Hello World!", "Hello World!");

	// Integer testing
	_testing_print(failed, passed, "--> 10", "--> %i", 10);
	_testing_print(failed, passed, "--> 100", "--> %i", 100);
	_testing_print(failed, passed, "--> 1000", "--> %i", 1000);
	_testing_print(failed, passed, "--> 10000", "--> %i", 10000);

	// Strings...
	_testing_print(failed, passed, "HELLO WORLD!", "%#s", "Hello World!");
	_testing_print(failed, passed, "He", "%.2s", "Hello World!");

	// Formatted string
	_testing_print(failed, passed, "Hello World!", "Hello $f!", "%s", "World");
	_testing_print(failed, passed, "Hello World!", "Hello $f!", "$f", "%s", "World");
	_testing_print(failed, passed, "Hello World!", "Hello $f!", "$f", "$f", "%s", "World");

	// Would this even happen?
	_testing_print(failed, passed, "Hello World 10!", "Hello $f!", "$f %d", "$f", "%s", "World", 10);
}

#include<wh-testing/unit.h>
#include<wh-sys/print.h>
#include<wh-posix/stdio.h>

#include<wh-core/debug/logger.h>

i64 some_cpp_func(wh_print_data_s* data, void* ptr) {
    return 0;
}

void simple(wh_unit_test_s* info) {
    char wh_buffer[1024] = { 0 };
    char std_buffer[1024] = { 0 };

    // Test 1
    wh_print(("Hello, World!", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH));
    snprintf(std_buffer, 1024, "Hello, World!");
    
    WH_TEST_STREQ(info, wh_buffer, "Hello, World!");
    WH_TEST_STREQ(info, wh_buffer, std_buffer);

    // Test 2
    wh_print(("--> %i", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH), 102);
    snprintf(std_buffer, 1024, "--> %i", 102);

    // Test 3
    wh_print(("Hello $$ world!", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH));
    WH_TEST_STREQ(info, wh_buffer, "Hello $ world!");

    // Test 3
    wh_print(("Hello %% world!", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH));
    WH_TEST_STREQ(info, wh_buffer, "Hello % world!");
}

void functions(wh_unit_test_s* info) {
    char wh_buffer[1024] = { 0 };
   
    // Registering test functions.
    wh_print_add_func("cpp", &some_cpp_func);

    // Testing ideal case.
    wh_print(("Some cpp -->$[cpp]", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH), nullptr);
    WH_TEST_STREQ(info, wh_buffer, "Some cpp -->");
    memset(wh_buffer, 0, 1024);

    // Open brace test
    wh_print(("Some cpp -->$[cpp", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH), nullptr);
    WH_TEST_STREQ(info, wh_buffer, "Some cpp -->cpp");
    memset(wh_buffer, 0, 1024);
}

i64 init(wh_unit_test_s* info) {
    wh_core_log_set_level(WH_LOG_LEVEL_ALL, 0);

    WH_TEST(info, simple(info));
    WH_TEST(info, functions(info));

    return 0;
}

i64 destructor(wh_unit_test_s* info) {
    return 0;
}

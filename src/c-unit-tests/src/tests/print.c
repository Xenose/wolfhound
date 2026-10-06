#include<wh-testing/unit.h>
#include<wh-sys/print.h>
#include<wh-posix/stdio.h>

void simple(wh_unit_test_s* info) {
    char wh_buffer[1024] = { 0 };
    char std_buffer[1024] = { 0 };

    // Test 1
    wh_print(("Hello, World!", .buffer = wh_buffer, .buffer_length = 1024, .flags = WH_PRINT_NO_FLUSH));
    snprintf(std_buffer, 1024, "Hello, World!");
    
    WH_TEST_STREQ(info, wh_buffer, "Hello, World!");
    WH_TEST_STREQ(info, wh_buffer, std_buffer);
}

i64 init(wh_unit_test_s* info) {
    simple(info);
    return 0;
}

i64 destructor(wh_unit_test_s* info) {
    return 0;
}

#include<wh-testing/unit.h>
#include<wh/string.h>
#include<wh-sys/debug/logger.h>

#include<wh-posix/errno.h>

i64 test_strcat(wh_unit_test_s* info) {
    int64_t error = 0;
    char buffer[256] = { 0 };

    // Easy test for wh_strcat
    error = 0;

    wh_strcat((buffer, 255), "Hello,", " ", "world!");
    WH_TEST_STREQ(info, "Hello, world!", buffer, "wh_strcat::world_test");
    WH_TEST_INT64EQ(info, 0l, error);

    error = 0;
    memset(buffer, 0, 256);
    wh_strcat((buffer, 255), "Hello,", " ", nullptr, "world!");
    WH_TEST_STREQ(info, "Hello, world!", buffer, "wh_strcat::world_test");
    WH_TEST_INT64EQ(info, 0l, error);

    error = 0;
    memset(buffer, 0, 256);
    wh_strcat((buffer, 10, .error = &error), "Hello,", " ", nullptr, "world!");
    WH_TEST_STREQ(info, "Hello, wor", buffer, "wh_strcat::world_test");
    WH_TEST_INT64EQ(info, (int64_t)ENOMEM, error);

    error = 0;
    memset(buffer, 0, 256);
    wh_strcat((.buffer_length = 10, .error = &error), "Hello,", " ", nullptr, "world!");
    WH_TEST_STREQ(info, "", buffer, "wh_strcat::world_test");
    WH_TEST_INT64EQ(info, (int64_t)EFAULT, error);

    error = 0;
    memset(buffer, 0, 256);
    wh_strcat((.error = &error), "Hello,", " ", nullptr, "world!");
    WH_TEST_STREQ(info, "", buffer, "wh_strcat::world_test");
    WH_TEST_INT64EQ(info, (int64_t)ENOBUFS, error);

    return 0;
}

i64 test_string_split(wh_unit_test_s* info) {
    int i = 0;
    int status = 0;
    i64 index = 0;
    ssize_t length = 0;
    char tmp[256] = { 0 };

    const char* string = "test,test,test,hello";
    const char* results[] = { "test", "test", "test", "hello" };

    // Testing items before the final item.
    do {
        status = wh_string_split(&length, &index, string, ",");

        memcpy(tmp, &string[index], length);
        WH_TEST_STREQ(info, results[i], tmp);
        memset(tmp, 0, length);

        // moving the test index
        ++i;
    } while(-1 != status);
    
    WH_TEST_INT64EQ(info, sizeof(results) / sizeof(results[0]), (i64)i);

    return 0;
}

i64 init(wh_unit_test_s* info) {
    WH_TEST(info, test_strcat(info));
    WH_TEST(info, test_string_split(info));
    return 0;
}

i64 destructor(wh_unit_test_s* info) {
    return 0;
}

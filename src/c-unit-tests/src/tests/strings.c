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
    i64 index = 0;
    size_t length = 0;
    char tmp[256] = { 0 };

    const char* string = "test,test,test,hello";

    // Testing items before the final item.
    while (nullptr != wh_string_split(&length, &index, string, ",")) {
        memcpy(tmp, &string[index - 1], length);
        WH_TEST_STREQ(info, "test", tmp);
        memset(tmp, 0, length);
    }

    // Final item in the split
    memcpy(tmp, &string[index], length);
    WH_TEST_STREQ(info, "hello", tmp);
    memset(tmp, 0, length);

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

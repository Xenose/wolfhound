#include<wh-testing/unit.h>
#include<wh/string.h>

#include<wh-posix/errno.h>

i64 init(wh_unit_test_s* info) {

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
    WH_TEST_INT64EQ(info, (int64_t)ENOBUFS, error + 1);

    return 0;
}

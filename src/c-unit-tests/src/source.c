#include<wh/debug/exceptions.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-posix/errno.h>

#include<wh-testing/unit.h>

#include<wh/string.h>


void test_string() {
    WH_TEST(wh_strcat) {
        int64_t error = 0;
        char buffer[256] = { 0 };

        // Easy test for wh_strcat
        wh_strcat((buffer, 255), "Hello,", " ", "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, world!", buffer, "wh_strcat::world_test");
       
        memset(buffer, 0, 256);
        wh_strcat((buffer, 255), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, world!", buffer, "wh_strcat::world_test");
        

        memset(buffer, 0, 256);
        wh_strcat((buffer, 10, .error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, wor", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)ENOMEM, error);
        
        memset(buffer, 0, 256);
        wh_strcat((.buffer_length = 10, .error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)EFAULT, error);

        memset(buffer, 0, 256);
        wh_strcat((.error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)ENOBUFS, error);

        WH_TEST_REPORT(wh_strcat);
    }
}

int main(int arc, char* const* arv) {
    test_string();
}

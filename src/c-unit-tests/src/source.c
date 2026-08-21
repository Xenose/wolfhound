#include<wh/debug/exceptions.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>

#include<wh-testing/unit.h>

#include<wh/string.h>

int main(int arc, char* const* arv) {
    WH_TEST(wh_strcat) {
        char buffer[256] = { 0 };

        // Easy test for wh_strcat
        wh_strcat((buffer, 255), "Hello,", " ", "world!");
        WH_TEST_STREQ(wh_strcat_test, "Hello, world!", buffer, "wh_strcat::world_test");

        WH_TEST_REPORT(wh_strcat_test);
    }
}

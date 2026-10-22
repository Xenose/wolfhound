#include<wh-testing/unit.h>
#include<wh-posix/stdio.h>
#include<wh/convert.h>

i64 test_numbers(wh_unit_test_s* info) {
    i64 result = 0;
    i64 excpected = 0;
    char buffer[256] = { 0 };

    wh_for(int, i, 100000) {
       result = wh_str2int(buffer, 256);
       excpected = strtol(buffer, nullptr, 10);
       
       WH_TEST_INT64EQ(info, result, excpected);
    }

    return 0;
}

i64 init(wh_unit_test_s* info) {
    test_numbers(info);
    return 0;
}

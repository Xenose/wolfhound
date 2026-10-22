#include<wh-testing/unit.h>
#include<wh/debug/exceptions.h>

#include<wh-posix/signal.h>
#include<wh-posix/stdlib.h>
#include<wh-sys/debug/logger.h>

i64 test_exceptions_happy(wh_unit_test_s* info) {
    const char* status = nullptr;

    wh_try {
        status = "passed";
    } wh_catch(wh_exception_s, e) {
        status = "failed";
    }

    WH_TEST_STREQ(info, status, "passed");
    status = nullptr;

    wh_try {
        status = "passed_01";

        wh_try {
            status = "passed_02";
        } wh_catch(wh_exception_s, e) {
            status = "failed_02";
        }
    } wh_catch(wh_exception_s, e) {
        status = "failed_01";
    }
    
    WH_TEST_STREQ(info, status, "passed_02");
    status = nullptr;


    wh_try {
        status = "passed_01";

        wh_try {
            status = "passed_02";

            wh_try {
                status = "passed_03";
            } wh_catch(wh_exception_s, e) {
                status = "failed_03";
            }
        } wh_catch(wh_exception_s, e) {
            status = "failed_02";
        }
    } wh_catch(wh_exception_s, e) {
        status = "failed_01";
    }
    
    WH_TEST_STREQ(info, status, "passed_03");
    status = nullptr;

    return 0;
}

i64 test_exceptions_throw(wh_unit_test_s* info) {
    int code = WH_EXCEPTION_NONE;
    const char* status = nullptr;

    wh_try {
        status = "failed";
        wh_throw(WH_EXCEPTION_UNKNOWN);
    } wh_catch(wh_exception_s, e) {
        code = e.error;
        status = "passed";
    }
    
    WH_TEST_INT64EQ(info, (i64)code, (i64)WH_EXCEPTION_UNKNOWN);
    WH_TEST_STREQ(info, status, "passed");

    code = 0;
    status = nullptr;

    return 0;
}

i64 test_exceptions_segfault(wh_unit_test_s* info) {
    i64 code = 0;
    const char* status = nullptr;

    wh_try {
        status = "failed";
        raise(SIGSEGV);
    } wh_catch(wh_exception_s, e) {
        code = e.error;
        status = "passed";
    }

    WH_TEST_INT64EQ(info, code, (i64)WH_EXCEPTION_SIGSEGV);
    WH_TEST_STREQ(info, status, "passed");

    code = 0;
    status = nullptr;

    return 0;
}

i64 test_exceptions_propagation(wh_unit_test_s* info) {
    i64 code = WH_EXCEPTION_NONE;
    int caught_outer = 0;
    int caught_inner = 0;

    wh_try {
        wh_try {
            wh_throw(WH_EXCEPTION_UNKNOWN);
        } wh_catch(wh_exception_s, e) {
            code = e.error;
            caught_inner = 1;
        }
    } wh_catch(wh_exception_s, e) {
        code = e.error;
        caught_outer = 1;
    }

    WH_TEST_INT64EQ(info, (i64)caught_inner, 1L);
    WH_TEST_INT64EQ(info, (i64)caught_outer, 0L);
    WH_TEST_INT64EQ(info, code, (i64)WH_EXCEPTION_UNKNOWN);

    return 0;
}

i64 init(wh_unit_test_s* info) {
    test_exceptions_happy(info);
    test_exceptions_throw(info);
    test_exceptions_segfault(info);
    test_exceptions_propagation(info);
    return 0;
}

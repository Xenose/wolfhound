#include<wh-testing/unit.h>


i8 _wh_test_func(wh_unit_test_s* info, const char* name) {
    if (nullptr != info->error.last_function) { 
        free((void*)info->error.last_function);
        info->error.last_function = nullptr;
    }

    info->error.last_function = strdup(name);
    return 0;
}

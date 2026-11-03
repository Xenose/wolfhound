#include<wh-posix/stdarg.h>
#include<wh-sys/print.h>
#include<wh-sys/debug/logger.h>
#include<wh/wolfhound.h>

#include<wh-core/common.h>
#include<wh-core/print.h>
#include<wh-core/debug/logger.h>

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args);

static i64 _wh_log_dummy(_wh_print_params print_params, _wh_log_params params, ...);
static i64 _wh_log_real(_wh_print_params print_params, _wh_log_params params, ...);

i64 (*_wh_log_va[])(_wh_print_params print_params, _wh_log_params params, va_list args) = {
    &_wh_log_real_va, // Emergency
    &_wh_log_real_va, // Alert
    &_wh_log_real_va, // Critical
    &_wh_log_real_va, // Error
    &_wh_log_real_va, // Warning
    &_wh_log_real_va, // Notice
    &_wh_log_real_va, // Info
    &_wh_log_real_va, // Debug
};

i64 (*_wh_log[])(_wh_print_params print_params, _wh_log_params params, ...) = {
    &_wh_log_real, // Emergency
    &_wh_log_real, // Alert
    &_wh_log_real, // Critical
    &_wh_log_real, // Error
    &_wh_log_real, // Warning
    &_wh_log_real, // Notice
    &_wh_log_real, // Info
    &_wh_log_real, // Debug
};

// Dummy functions doesn't need these warnings
WH_IGNORE_UNUSED_PARAMS()
static i64 _wh_log_dummy(_wh_print_params print_params, _wh_log_params params, ...) { return 0; }
static i64 _wh_log_dummy_va(_wh_print_params print_params, _wh_log_params params, va_list args) { return 0; }
WH_IGNORE_END()

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args) {
    char* _buffer = print_params.buffer;

    if (nullptr == print_params.buffer) {
        _buffer = wh_core_print_buffer(&print_params.buffer_length);
    }

    i64 used = wh_print((
        "[ %s ] $t :: \033[90m%s::%d::%s -->\033[0m ",
        2, _buffer, 8096, 0, WH_PRINT_NO_FLUSH),
        // Log arguments
        params.level,
        "%H:%M:%S",
        params.file,
        params.line,
        params.func
    );

    print_params.fd = 2;
    print_params.offset += used;
    print_params.buffer = _buffer;
    print_params.buffer_length = 8095;
    print_params.flags |= WH_PRINT_ADD_NEW_LINE;

    used += _wh_print_va(print_params, args);
    return used;
}

static i64 _wh_log_real(_wh_print_params print_params, _wh_log_params params, ...) {
    va_list args;
    i64 used = 0;

    va_start(args, params);
    used += _wh_log_real_va(print_params, params, args);
    va_end(args);

    return used;
}

void _wh_log_init(_wh_log_init_params params) {
}

// if updated remember to update the wh-core/debug/logger also.
void wh_log_set_level(i64 from_level, u8 state) {
    i64 to_level = from_level;
    
    wh_core_log_set_level(from_level, state);

    if (WH_LOG_LEVEL_ALL == from_level) {
        to_level = WH_LOG_LEVEL_DEBUG;
        from_level = WH_LOG_LEVEL_EMERGENCY;
    }

    for (i64 i = from_level; i <= to_level; i++) {
        if (0 == state) {
            _wh_log[i] = &_wh_log_dummy;
            _wh_log_va[i] = &_wh_log_dummy_va;
        } else {
            _wh_log[i] = &_wh_log_real;
            _wh_log_va[i] = &_wh_log_real_va;
        }
    }
    
}

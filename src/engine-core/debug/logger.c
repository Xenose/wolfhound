#include<wh-posix/stdio.h>
#include<wh-posix/stdarg.h>

#include<wh-types/print.h>
#include<wh-params/print.h>

#include<wh-core/common.h>
#include<wh-core/macros.h>
#include<wh-core/print.h>

static i64 _wh_core_log_dummy_va(_wh_print_params print_params, _wh_log_params params, va_list args);
static i64 _wh_core_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args);
static i64 _wh_core_log_dummy(_wh_print_params print_params, _wh_log_params params, ...);
static i64 _wh_core_log_real(_wh_print_params print_params, _wh_log_params params, ...);


i64 (*_wh_core_log_va[])(_wh_print_params print_params, _wh_log_params params, va_list args) = {
    &_wh_core_log_real_va, // Emergency
    &_wh_core_log_real_va, // Alert
    &_wh_core_log_real_va, // Critical
    &_wh_core_log_real_va, // Error
    &_wh_core_log_real_va, // Warning
    &_wh_core_log_real_va, // Notice
    &_wh_core_log_real_va, // Info
    &_wh_core_log_real_va, // Debug
};

i64 (*_wh_core_log[])(_wh_print_params print_params, _wh_log_params params, ...) = {
    &_wh_core_log_real, // Emergency
    &_wh_core_log_real, // Alert
    &_wh_core_log_real, // Critical
    &_wh_core_log_real, // Error
    &_wh_core_log_real, // Warning
    &_wh_core_log_real, // Notice
    &_wh_core_log_real, // Info
    &_wh_core_log_real, // Debug
};


WH_IGNORE_UNUSED_PARAMS()
i64 _wh_core_log_dummy_va(_wh_print_params print_params, _wh_log_params params, va_list args) WH_IGNORE_END() {
    return 0;
}

i64 _wh_core_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args) {
    i64 count = 0;
    size_t length = (size_t)print_params.buffer_length;
    int offset = 0;
    char* buffer = print_params.buffer;

    if (nullptr == buffer) {
        length = WH_CORE_PRINT_BUFFER_LENGTH;
        buffer = wh_core_print_buffer();
    }

    offset = snprintf(
        buffer,
        length,
        "[ %s ] core :: \033[90m%s::%ld::%s -->\033[0m ",
        // Log arguments
        params.level,
        params.file,
        params.line,
        params.func
    );

    offset += vsnprintf(
        &buffer[offset],
        length - (size_t)offset,
        print_params.format,
        args
    );

    buffer[offset++] = '\n';
    write(1, buffer, length);
    return 0;
}
WH_IGNORE_UNUSED_PARAMS()
i64 _wh_core_log_dummy(_wh_print_params print_params, _wh_log_params params, ...) WH_IGNORE_END() {
    return 0;
}

static i64 _wh_core_log_real(_wh_print_params print_params, _wh_log_params params, ...) {
    i64 out = 0;
    va_list args;

    va_start(args, params);
    out = _wh_core_log_real_va(print_params, params, args);
    va_end(args);

    return out;
}

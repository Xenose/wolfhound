#include<stdarg.h>

#include<wh/print.h>
#include<wh/debug/logger.h>
#include<wh/wolfhound.h>

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args);

static i64 _wh_log_dummy(_wh_print_params print_params, _wh_log_params params, ...);
static i64 _wh_log_real(_wh_print_params print_params, _wh_log_params params, ...);

#if !(WH_SYSTEM&WH_SYS_TCC)
	static wh_thread char _buffer[8096] = { 0 };
#endif

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

static i64 _wh_log_dummy(_wh_print_params print_params, _wh_log_params params, ...) {
	return 0;
}

static i64 _wh_log_dummy_va(_wh_print_params print_params, _wh_log_params params, va_list args) {
	return 0;
}

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args) {
	#if (WH_SYSTEM&WH_SYS_TCC)
		char _buffer[8096] = { 0 };
	#endif

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

void wh_log_set_level(i64 level, u8 state) {
	if (0 == state) {
		_wh_log[level] = &_wh_log_dummy;
		_wh_log_va[level] = &_wh_log_dummy_va;
	} else {
		_wh_log[level] = &_wh_log_real;
		_wh_log_va[level] = &_wh_log_real_va;
	}
}

#include<stdarg.h>

#include<wh/print.h>
#include<wh/debug.h>
#include<wh/wolfhound.h>

extern void _wh_log_init_raylib(_wh_log_init_params* params);

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args);

static i64 _wh_log_dummy(_wh_print_params print_params, _wh_log_params params, ...);
static i64 _wh_log_real(_wh_print_params print_params, _wh_log_params params, ...);
	
wh_thread char _buffer[8096] = { 0 };

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

static i64 _wh_log_real_va(_wh_print_params print_params, _wh_log_params params, va_list args) {
	u64 used = wh_print((
		"[ %s ] \033[90m%s::%d in %s -->\033[0m "
		, 2, _buffer, 8096, 0, WH_PRINT_NO_FLUSH),

		params.level,
		params.func,
		params.line,
		params.file
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
	switch (params.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_log_init_raylib(&params);
			break;
	}
}

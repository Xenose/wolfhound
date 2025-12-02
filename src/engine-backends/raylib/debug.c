#include<wh/debug/logger.h>
#include<wh-backend/raylib/raylib.h>

void _wh_log_raylib(int msgType, const char *text, va_list args) {
	switch (msgType) {
		default:
		case RAY_LOG_TRACE:
			wh_log_va_debug((text), args);
			break;
		case RAY_LOG_DEBUG:
			wh_log_va_info((text), args);
			break;
		case RAY_LOG_INFO:
			wh_log_va_notice((text), args);
			break;
		case RAY_LOG_WARNING:
			wh_log_va_warning((text), args);
			break;
		case RAY_LOG_ERROR:
			wh_log_va_error((text), args);
			break;
		case RAY_LOG_FATAL:
			wh_log_va_critical((text), args);
			break;
	}
}

void _wh_log_init_raylib(_wh_log_init_params* params) {
	wh_log_info(("setting up raylib logging!"));
	raylib.set_trace_log_callback(&_wh_log_raylib);
}

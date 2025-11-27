#ifndef _wh_header_debug_
#define _wh_header_debug_

#include<wh/common.h>
#include<wh/print.h>

typedef struct {
	const char* file;
	const char* func;
	const char* level;
	i64 line;
} _wh_log_params;

typedef struct {
	u64 mode;
} _wh_log_init_params;

enum { 
	WH_LOG_LEVEL_EMERGENCY,
	WH_LOG_LEVEL_ALERT,
	WH_LOG_LEVEL_CRITICAL,
	WH_LOG_LEVEL_ERROR,
	WH_LOG_LEVEL_WARNING,
	WH_LOG_LEVEL_NOTICE,
	WH_LOG_LEVEL_INFO,
	WH_LOG_LEVEL_DEBUG
};

extern i64 (*_wh_log_va[])(_wh_print_params print_params, _wh_log_params params, va_list args);
extern i64 (*_wh_log[])(_wh_print_params print_params, _wh_log_params params, ...);

extern void _wh_log_init(_wh_log_init_params params);
extern void wh_log_set_level(i64 level, u8 state);

/* [MD_DOC]
 * # wh_log_* and wh_log_va_*
 * These functions are wolfhounds main logging functions, they
 * are wrappers around the wh_print and wh_print_va functions
 * so all formats supported by these functions are supported by
 * these functions.
 *
 * ## example
 * ```bash
 * [ LOG_LEVEL  ] FILE.C::LINE::FUNCTION --> MASSAGE
 * ```
 */
#define wh_log_va_emergency(x, _args_)		WH_EPF(_wh_log_va[0]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[35mEMERGENCY\033[0m",		__LINE__ }, _args_))
#define wh_log_va_alert(x, _args_)			WH_EPF(_wh_log_va[1]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[95mALERT\033[0m    ",		__LINE__ }, _args_))
#define wh_log_va_critical(x, _args_)		WH_EPF(_wh_log_va[2]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[31mCRITICAL\033[0m ",		__LINE__ }, _args_))
#define wh_log_va_error(x, _args_)			WH_EPF(_wh_log_va[3]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[91mERROR\033[0m    ",		__LINE__ }, _args_))
#define wh_log_va_warning(x, _args_)		WH_EPF(_wh_log_va[4]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[33mWARNING\033[0m  ",		__LINE__ }, _args_))
#define wh_log_va_notice(x, _args_)			WH_EPF(_wh_log_va[5]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[96mNOTICE\033[0m   ",		__LINE__ }, _args_))
#define wh_log_va_info(x, _args_)			WH_EPF(_wh_log_va[6]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[36mINFO\033[0m     ",		__LINE__ }, _args_))
#define wh_log_va_debug(x, _args_)			WH_EPF(_wh_log_va[7]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[90mDEBUG\033[0m    ",		__LINE__ }, _args_))

#define wh_log_emergency(x, ...)		WH_EPF(_wh_log[0]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[35mEMERGENCY\033[0m",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_alert(x, ...)			WH_EPF(_wh_log[1]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[95mALERT\033[0m    ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_critical(x, ...)		WH_EPF(_wh_log[2]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[31mCRITICAL\033[0m ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_error(x, ...)			WH_EPF(_wh_log[3]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[91mERROR\033[0m    ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_warning(x, ...)		WH_EPF(_wh_log[4]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[33mWARNING\033[0m  ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_notice(x, ...)			WH_EPF(_wh_log[5]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[96mNOTICE\033[0m   ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_info(x, ...)			WH_EPF(_wh_log[6]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[36mINFO\033[0m     ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))
#define wh_log_debug(x, ...)			WH_EPF(_wh_log[7]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[90mDEBUG\033[0m    ",		__LINE__ } __VA_OPT__(, __VA_ARGS__)))


/* [MD_DOC]
 * # wh_log_init
 * ```c
 *	void wh_log_init(u64 mode)
 * ```
 */
#define wh_log_init(...)	_wh_log_init((_wh_log_init_params) { __VA_ARGS__ })

#endif /* _wh_header_debug_ */

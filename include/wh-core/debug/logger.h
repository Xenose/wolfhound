#ifndef _wh_header_core_debug_logger_
#define _wh_header_core_debug_logger_

#include <wh-sys/print.h>

extern i64 (*_wh_core_log_va[])(_wh_print_params print_params, _wh_log_params params, va_list args);
extern i64 (*_wh_core_log[])(_wh_print_params print_params, _wh_log_params params, ...);

#define wh_core_va_emergency(x, _args_) WH_EPF(_wh_core_log_va[0]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[35mEMERGENCY\033[0m", __LINE__ }, _args_))
#define wh_core_va_alert(x, _args_)     WH_EPF(_wh_core_log_va[1]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[95mALERT\033[0m    ", __LINE__ }, _args_))
#define wh_core_va_critical(x, _args_)  WH_EPF(_wh_core_log_va[2]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[31mCRITICAL\033[0m ", __LINE__ }, _args_))
#define wh_core_va_error(x, _args_)     WH_EPF(_wh_core_log_va[3]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[91mERROR\033[0m    ", __LINE__ }, _args_))
#define wh_core_va_warning(x, _args_)   WH_EPF(_wh_core_log_va[4]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[33mWARNING\033[0m  ", __LINE__ }, _args_))
#define wh_core_va_notice(x, _args_)    WH_EPF(_wh_core_log_va[5]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[96mNOTICE\033[0m   ", __LINE__ }, _args_))
#define wh_core_va_info(x, _args_)      WH_EPF(_wh_core_log_va[6]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[36mINFO\033[0m     ", __LINE__ }, _args_))
#define wh_core_va_debug(x, _args_)     WH_EPF(_wh_core_log_va[7]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[90mDEBUG\033[0m    ", __LINE__ }, _args_))

#define wh_core_emergency(x, ...)       WH_EPF(_wh_core_log[0]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[35mEMERGENCY\033[0m", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_alert(x, ...)           WH_EPF(_wh_core_log[1]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[95mALERT\033[0m    ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_critical(x, ...)        WH_EPF(_wh_core_log[2]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[31mCRITICAL\033[0m ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_error(x, ...)           WH_EPF(_wh_core_log[3]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[91mERROR\033[0m    ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_warning(x, ...)         WH_EPF(_wh_core_log[4]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[33mWARNING\033[0m  ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_notice(x, ...)          WH_EPF(_wh_core_log[5]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[96mNOTICE\033[0m   ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_info(x, ...)            WH_EPF(_wh_core_log[6]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[36mINFO\033[0m     ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))
#define wh_core_debug(x, ...)           WH_EPF(_wh_core_log[7]((_wh_print_params) { WH_VA_ARGS x }, (_wh_log_params) {  __FILENAME__, __func__, "\033[90mDEBUG\033[0m    ", __LINE__ } WH_VA_OPT(__VA_ARGS__)))


#endif /* _wh_header_core_debug_logger_ */

#ifndef _wh_header_error_
#define _wh_header_error_

#include<wh/common.h>

typedef struct {
	i64 number;
} _wh_errno_str_params;

typedef struct {
	i64 number;
} _wh_vk_status_params;

extern const char* _wh_errno_str(_wh_errno_str_params params);
extern const char* _wh_vk_status_str(_wh_vk_status_params params);

/* [MD_DOC]
 *  ## wh_error_str
 */
#define wh_errno_str(...) _wh_errno_str((_wh_errno_str_params) { __VA_ARGS__ })

/* [MD_DOC]
 *  ## wh_vk_status_str
 */
#define wh_vk_status_str(...) _wh_vk_status_str((_wh_vk_status_params) { __VA_ARGS__ })

#endif /* _wh_header_error_ */

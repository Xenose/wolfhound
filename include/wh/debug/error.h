#ifndef _wh_header_error_
#define _wh_header_error_

#include<wh-core/common.h>

WH_C()

typedef struct {
    i64 number;
} _wh_errno_str_params;

typedef struct {
    i64 number;
} _wh_vk_status_params;

extern const char* _wh_errno_str(_wh_errno_str_params params);
extern const char* _wh_vk_status_str(_wh_vk_status_params params);

/* [MD_DOC:wh_error_str]
 *  ## wh_error_str
 */
#define wh_errno_str(...) _wh_errno_str((_wh_errno_str_params) { __VA_ARGS__ })

/* [MD_DOC:wh_vk_status_str]
 *  ## wh_vk_status_str
 */
#define wh_vk_status_str(...) _wh_vk_status_str((_wh_vk_status_params) { __VA_ARGS__ })

WH_C_END()

#endif /* _wh_header_error_ */

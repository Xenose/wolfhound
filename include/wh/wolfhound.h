#ifndef _wh_header_wh_
#define _wh_header_wh_

#include<wh/common.h>
#include<wh/memory.h>
#include<wh/params/wolfhound.h>

WH_C()

extern wh_instance_s* _wh_init(_wh_init_params params);
extern void _wh_loop(_wh_loop_params params);
extern int64_t _wh_end(_wh_end_params params);

/* [MD_DOC]
 * # wh_init
 * ```c
 *	wh_instance_s* wh_init()
 * ```
 */
#define wh_init(...) WH_EPF(_wh_init((_wh_init_params) { __VA_ARGS__ }))

#ifndef __cplusplus
/* [MD_DOC]
 */
#define wh_loop(...) WH_EPF(_wh_loop((_wh_loop_params) { __VA_ARGS__ }))
#define wh_end(...) WH_EPF(_wh_end((_wh_end_params) { __VA_ARGS__ }))
#endif /* __cplusplus */

WH_C_END()

#endif /* _wh_header_wh_ */

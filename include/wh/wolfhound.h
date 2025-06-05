#ifndef _header_wh_
#define _header_wh_

#include<wh/common.h>
#include<wh/memory.h>
#include<wh/params/wolfhound.h>

#include<stdint.h>
#include<SDL3/SDL.h>

WH_C

extern wh_instance_s* _wh_init(_wh_init_params params);
extern void _wh_loop(_wh_loop_params params);
extern int64_t _wh_end(_wh_end_params params);

/* [MD_DOC]
 * # wh_init
 * ```c
 *	wh_instance_s* wh_init()
 * ```
 */
#define wh_init(...) _wh_init((_wh_init_params) { __VA_ARGS__ })
#define wh_loop(...) _wh_loop((_wh_loop_params) { __VA_ARGS__ })
#define wh_end(...) _wh_end((_wh_end_params) { __VA_ARGS__ })

WH_C_END

#endif /* _header_wolfhound_ */

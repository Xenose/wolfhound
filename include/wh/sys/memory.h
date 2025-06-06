#ifndef _wh_header_sys_memory_
#define _wh_header_sys_memory_

#include<wh/common.h>

WH_C()

// =====================================================================================
// Parameter structs
// =====================================================================================

typedef struct {
	u64 bytes;
} _wh_sys_memreq_params;

// System dependent code
extern void* _wh_sys_memreq(_wh_sys_memreq_params params);

#define wh_sys_memreq(...)	_wh_sys_memreq((_wh_sys_memreq_params) { __VA_ARGS__ })

WH_C_END()
#endif /* _wh_header_sys_memory_ */


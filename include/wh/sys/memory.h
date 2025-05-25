#ifndef _wh_header_sys_memory_
#define _wh_header_sys_memory_

#include<wh/common.h>

// =====================================================================================
// Parameter structs
// =====================================================================================

typedef struct {
	u64 bytes;
} _wh_sys_memreq_params;

// System dependent code
extern void* _wh_sys_memreq(_wh_sys_memreq_params params);

#define wh_sys_memreq(...)	_wh_sys_memreq((_wh_sys_memreq_params) { __VA_ARGS__ })

#endif /* _wh_header_sys_memory_ */

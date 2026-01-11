#ifndef _wh_header_sys_memory_
#define _wh_header_sys_memory_

#include<wh-common/common.h>

WH_C()

// =====================================================================================
// Parameter structs
// =====================================================================================

typedef struct {
	u64 bytes;
} _wh_sys_memreq_params;

typedef struct {
	void* ptr;
	size_t len;
} _wh_sys_memrel_params;

// System dependent code
extern void* _wh_sys_memreq(_wh_sys_memreq_params params);
extern void _wh_sys_memrel(_wh_sys_memrel_params params);

#define wh_sys_memreq(...)	WH_EPF(_wh_sys_memreq((_wh_sys_memreq_params) { __VA_ARGS__ }))
#define wh_sys_memrel(...) WH_EPF(_wh_sys_memrel((_wh_sys_memrel_params) { __VA_ARGS__ }))

WH_C_END()
#endif /* _wh_header_sys_memory_ */


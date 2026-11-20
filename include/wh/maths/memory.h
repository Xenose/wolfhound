#ifndef _wh_header_maths_memory_
#define _wh_header_maths_memory_

#include <wh-core/common.h>

WH_C()

extern i64 wh_align(i64 value, i64 align);
extern u64 wh_ualign(u64 value, u64 align);

WH_C_END()

#endif /* _wh_header_maths_memory_ */

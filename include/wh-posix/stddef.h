#ifndef _wh_header_posix_stddef_
#define _wh_header_posix_stddef_

#include<wh-core/common.h>

WH_C()

#include<stddef.h>

#if !(WH_SYSTEM&WH_SYS_POSIX)
#endif

WH_C_END()

#endif /* _wh_header_posix_stddef_ */

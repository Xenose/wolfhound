#ifndef _wh_header_sys_library_
#define _wh_header_sys_library_

#include<wh-core/common.h>
#include<wh-types/library.h>
#include<wh-params/library.h>

extern wh_lib_s _wh_libopen(_wh_libopen_params params);
extern void* _wh_libget(_wh_libget_params params);
extern i8 _wh_libfind(const char* name, char** buffer, u64 length);

#ifndef WOLFHUND_NO_MACROS
    #define wh_libopen(...)	WH_EPF(_wh_libopen((_wh_libopen_params){ __VA_ARGS__ }))
    #define wh_libget(...)	WH_EPF(_wh_libget((_wh_libget_params){ __VA_ARGS__ }))
#endif

#endif /* _wh_header_sys_library_ */

#ifndef _wh_header_signalar_
#define _wh_header_signalar_

#include <wh-core/common.h>
#include <wh/wolfhound.h>

typedef struct {
    const char* name;
} _wh_signalar_init_params;

extern i8 _wh_signalar_init(_wh_signalar_init_params params);

#define wh_signalar_init(...) WH_EPF(_wh_signalar_init((_wh_signalar_init_params) { __VA_ARGS__ }))

#endif /* _wh_header_signalar_ */

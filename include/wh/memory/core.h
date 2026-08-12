#ifndef _wh_header_memory_copy_
#define _wh_header_memory_copy_

#include <wh-core/common.h>

typedef struct {
    const void* c0;
    const void* c1; 
    size_t length;
    const void* mask;
} _wh_memcmp_mask_params;

extern i64 _wh_memcmp_mask(_wh_memcmp_mask_params params);

#define wh_memcmp_mask(...) WH_EPF(_wh_memcmp_mask((_wh_memcmp_mask_params) { __VA_ARGS__ }))

#endif /* _wh_header_memory_copy_ */

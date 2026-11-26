#ifndef _wh_header_types_stack_
#define _wh_header_types_stack_

#include<wh-core/common.h>

typedef struct {
    union {
        void* ptr;
        u8* bytes;
    };

    uintptr_t size;
} wh_raw_stack_s;

#endif /* _wh_header_types_stack_ */

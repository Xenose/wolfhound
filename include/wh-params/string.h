#ifndef _wh_header_params_string_
#define _wh_header_params_string_

#include<wh-core/common.h>

typedef struct {
    char* buffer;
    u64 buffer_length;
    u64 offset;
    i64* error;
} _wh_strcat_params;

typedef struct {
    wh_string_s* str;
} _wh_string_append_params;

typedef struct {
    const char* key;
    const char* str;
    u64 str_length;
    u64 key_length;
    i64* error;
} _wh_strstr_params;

#endif /* _wh_header_params_string_ */

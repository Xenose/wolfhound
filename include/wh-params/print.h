#ifndef _wh_header_params_print_
#define _wh_header_params_print_

#include<wh-types/print.h>
#include<wh-core/common.h>

typedef struct {
    wh_print_data_s* data; 
    u64 needed;
} _wh_print_buffer_check_params;

typedef struct {
    const char* format;
    i64 fd;
    char* buffer;
    i64 buffer_length;
    i64 offset;
    u64 flags;
} _wh_print_params;

typedef struct {
    const char* key;
    i64 (*func)(wh_print_data_s* data, void* ptr);
} _wh_print_add_func_params;

#endif /* _wh_header_params_print_ */

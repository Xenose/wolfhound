#ifndef _wh_header_types_print_
#define _wh_header_types_print_

#include<wh-core/common.h>

typedef struct {
    u64 left;       // %XX
    u64 right;      // %.XX

    struct {
        u8 length_set       : 1;    // .XX
        u8 alt_form         : 1;    // #
        u8 left_align       : 1;    // -
        u8 zero_pad         : 1;    // 0
        u8 space_pad        : 1;    // ' '
        u8 force_sign       : 1;    // +
        u8 thousand_group   : 1;    // '
        u8 long_value       : 1;    // l
        u8 llong_value      : 1;    // ll
    } flags;
} wh_print_format_s;

typedef struct {
    char* start;
    char* format;
    char* buffer;
    i64 length;     // length of buffer
    i64 written;    // number of charters written
    i64 fd;

    wh_print_format_s print_format;
} wh_print_data_s;

typedef struct {
    const char* file;
    const char* func;
    const char* level;
    i64 line;
} _wh_log_params;

typedef struct {
    u64 mode;
} _wh_log_init_params;

#endif /* _wh_header_types_print_ */

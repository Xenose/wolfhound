#ifndef _wh_header_data_http
#define _wh_header_data_http

#include<wh-core/common.h>

typedef enum {
    HTTP_REQUEST_TYPE_CONNECT,
    HTTP_REQUEST_TYPE_DELETE,
    HTTP_REQUEST_TYPE_GET,
    HTTP_REQUEST_TYPE_HEAD,
    HTTP_REQUEST_TYPE_OPTION,
    HTTP_REQUEST_TYPE_PATCH,
    HTTP_REQUEST_TYPE_POST,
    HTTP_REQUEST_TYPE_PRI,
    HTTP_REQUEST_TYPE_PUT,
    HTTP_REQUEST_TYPE_QUERY,
    HTTP_REQUEST_TYPE_TRACE,
} http_request_type_e;

typedef struct {
    // Content negotiation
    u8 keep_alive : 1;
    u8 upgrade : 1;
} wh_http_header_flags_s;

typedef struct {
    struct_type stype;
    http_request_type_e request_type;
    wh_http_header_flags_s flags;

    // Caching
    time_t age;
    time_t expires;

    // Conditionals
    time_t last_modified;

    // Message body information
    u64 content_length;

    // Request context
    
    // Other
    time_t date;
} wh_http_header_s;

#endif /* _wh_header_data_http */

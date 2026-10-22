#ifndef _wh_header_data_json
#define _wh_header_data_json

#include <wh-core/common.h>

typedef struct {
    struct_type stype;
    u64 hash_id;
    wh_string_s key;
    void* data;
} wh_json_node_s;

typedef struct {
    struct_type stype;
    u64 count;
    wh_json_node_s* entries;
} wh_json_s;

#endif /* _wh_header_data_json_ */

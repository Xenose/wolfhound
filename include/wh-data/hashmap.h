#ifndef _wh_header_data_hashmap_
#define _wh_header_data_hashmap_

#include<wh/common.h>

typedef struct {
	void* data;
	char* key;
} wh_hashmap_slot_string_s;

typedef struct {
	void* data;
	i64 key;
} wh_hashmap_slot_i64_s;

typedef struct {
	struct_type stype;
	void* slots;
	u64 slot_count;
} wh_hashmap_s;

typedef struct {
	struct_type stype;
	u64 init_size;
} _wh_hashmap_init_params;

extern wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params);

#endif /* _wh_header_data_hashmap_ */

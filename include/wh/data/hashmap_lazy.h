#ifndef _wh_header_data_hashmap_lazy_
#define _wh_header_data_hashmap_lazy_

#include<wh/common.h>
#include<wh/memory.h>

typedef struct {
	struct_type stype;
	
	const char* key;
	void* data;
} wh_hashmap_lazy_entry_s;

typedef struct {
	struct_type stype;
	wh_heap_header_s* heap;
	u64 count;
	u64 data_size;
	wh_hashmap_lazy_entry_s* entries;
} wh_hashmap_lazy_s;

typedef struct {
	wh_hashmap_lazy_s* map;
	const char* key;
} _wh_hashmap_lazy_insert_params;


extern void _wh_hashmap_lazy_insert(_wh_hashmap_lazy_insert_params params, ...);

#define wh_hashmap_lazy_insert(x, ...) _wh__hashmap_lazy_insert((_wh_hashmap_lazy_insert_params) { WH_VA_ARGS x }, __VA_ARGS__)

#endif /* _wh_header_data_hashmap_lazy_ */

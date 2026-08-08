#ifndef _wh_header_data_hashmap_lazy_
#define _wh_header_data_hashmap_lazy_

#include<wh-core/common.h>
#include<wh-sys/memory.h>

typedef struct {
    struct_type stype;
    const char* key;
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
    void* data;
} _wh_hashmap_lazy_insert_params;

typedef struct {
    wh_hashmap_lazy_s* map;
    const char* key;
} _wh_hashmap_lazy_get_params;

extern wh_hashmap_lazy_s _wh_hashmap_lazy_create(wh_heap_header_s* heap, u64 count, u64 data_size);
extern void _wh_hashmap_lazy_insert(_wh_hashmap_lazy_insert_params params);
extern void* _wh_hashmap_lazy_get(_wh_hashmap_lazy_get_params params);

#define wh_hashmap_lazy_insert(...) _wh_hashmap_lazy_insert((_wh_hashmap_lazy_insert_params) { __VA_ARGS__ })
#define wh_hashmap_lazy_get(_type_, ...) (_type_)_wh_hashmap_lazy_get((_wh_hashmap_lazy_get_params) { __VA_ARGS__ })

#endif /* _wh_header_data_hashmap_lazy_ */

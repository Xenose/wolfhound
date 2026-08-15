#ifndef _wh_header_data_dynamic_array
#define _wh_header_data_dynamic_array

#include <wh-core/common.h>
#include <wh-types/memory.h>

typedef struct {
    struct_type stype;
    wh_atomic_lock_s lock;

    union {
        wh_heap_header_s heap;
        wh_sysmem_s sysmem;
        void* memory;
    };

    u64 type_size;
    u64 node_count;

    void* head;
    void* tail;
} wh_darray_s;

typedef struct {
    struct_type stype;
    wh_darray_s* array;
    u64 type_size;
    u64 count;
} _wh_darray_init_params;

typedef struct {
    wh_darray_s* array;
    u64 index;
} _wh_darray_get_params;

typedef struct {
    wh_darray_s* array;
    u64 index;
    void* value;
} _wh_darray_set_params;

typedef struct {
    wh_darray_s* array;
} _wh_darray_push_back_params;

typedef struct {
    wh_darray_s* array;
    u64 index;
} _wh_darray_delete_param;

typedef struct {
    wh_darray_s* array;
    void (*loop)();
} _wh_darray_for_each_params;

extern void _wh_darray_init(_wh_darray_init_params params);
extern void* _wh_darry_get(_wh_darray_get_params params);
extern void* _wh_darray_set(_wh_darray_set_params params);

#define wh_darray_init(...) _wh_darray_init((_wh_darray_init_params){ __VA_ARGS__ })
#define wh_darray_get(...)  _wh_darry_get((_wh_darray_get_params){ __VA_ARGS__ })
#define wh_darray_set(...) _wh_darray_set((_wh_darray_set_params){ __VA_ARGS__ })

#endif /* _wh_header_data_dynamic_array_ */

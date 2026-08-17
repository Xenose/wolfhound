#ifndef _wh_header_data_dynamic_array
#define _wh_header_data_dynamic_array

#include <wh-core/common.h>
#include <wh-types/memory.h>

WH_C()

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
    i64 count;
} _wh_darray_resize_params;

typedef struct {
    wh_darray_s* array;
    u64 index;
} _wh_darray_delete_param;

typedef struct {
    wh_darray_s* array;
    void (*loop)(u64 index, void* data);
} _wh_darray_for_each_params;

extern void _wh_darray_init(_wh_darray_init_params params);
extern void* _wh_darry_get(_wh_darray_get_params params);
extern void* _wh_darray_set(_wh_darray_set_params params);
extern i8 _wh_darray_resize(_wh_darray_resize_params params);
extern void _wh_darray_for_each(_wh_darray_for_each_params params);

#ifndef __cplusplus
    /* [MD_DOC]
     * Creates a dynamic array with the need memory and parameters set
     * depending on the inputted type.
     *
     * TODO :: set the return on error to -1
     */
    #define wh_darray_init(...) _wh_darray_init((_wh_darray_init_params){ __VA_ARGS__ })

    /* [MD_DOC]
     * Gets the element of the index and will return nullptr
     * on error, for example trying to access memory outside
     * the index range.
     */
    #define wh_darray_get(...)  _wh_darry_get((_wh_darray_get_params){ __VA_ARGS__ })

    /* [MD_DOC]
     * Sets the value at the index of the array, if a error
     * happens nullptr is returned and on success the value
     * in the array is returned, example of error is when
     * trying to access memory outside its range.
     */
    #define wh_darray_set(...) _wh_darray_set((_wh_darray_set_params){ __VA_ARGS__ })

    /* [MD_DOC]
     * This function will resize the array by +N or -N given to
     * it, -1 is returned on error and will not be resized in this
     * case.
     */
    #define wh_darray_resize(...) _wh_darray_resize((_wh_darray_resize_params){ __VA_ARGS__ })

    /* [MD_DOC]
     */
    #define wh_darray_for_each(...) _wh_darray_for_each((_wh_darray_for_each_params){ __VA_ARGS__ })
#endif

WH_C_END()

#endif /* _wh_header_data_dynamic_array_ */

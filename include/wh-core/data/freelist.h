#ifndef _wh_header_core_freelist_
#define _wh_header_core_freelist_


#define WH_FREELIST_FLAG_USED   0x0001

#define WH_FREELIST(T, _name_, ...) \
    struct _##_name_##_freelist_struct { \
        _##_name_##_freelist_struct* next; \
        _##_name_##_freelist_struct* next_free; \
        _##_name_##_freelist_struct* previous; \
        uint64_t flags; \
        size_t count; \
        size_t free; \
    } _name_; typedef struct _##_name_##_freelist_struct

#define WH_FREELIST_RESIZE(_var_, _func_resize_)

#define WH_FREELIST_INSERT(_var_, _value_)

#define WH_FREELIST_DELETE(_var_, _index_, _func_destructor_)

#define WH_FREELIST_SEARCH(_var_, _value_)

#endif /* _wh_header_core_freelist_ */

#ifndef _wh_header_core_data_hashmap_
#define _wh_header_core_data_hashmap_

#include<wh-core/common.h>

#define WH_HASHMAP(T, _name_, _func_, ...) \
    struct _##_name_##_hashmap_struct { \
        size_t count; \
        size_t slots; \
        size_t (*hash)(const u8* ptr, void* data); \
        T* array; \
        __VA_ARGS__ \
    } _name_ = { .hash = _func_ }; typedef struct _##_name_##_hashmap_struct

#define WH_HASHMAP_VALUE(_var_, _key_) \
    (_var_)->array[(_var_)->hash(_key_, (_var_)->slots, (_var_)->count)]

#define WH_HASHMAP_RESIZE(_var_, _count_, _func_) \
    (_var_)->array = _func_((void*)_var_, _count_, sizeof((_var_)->array[0]))

#define WH_HASHMAP_VALUE_BY_INDEX(_var_, _index_) \
    (_var_)->array[_index_]

#define WH_HASHMAP_USED(_var_) \
    (_var_)->count

#define WH_HASHMAP_CAPACITY(_var_) \
    (_var_)->slots

#endif /* _wh_header_core_data_hashmap_ */ 

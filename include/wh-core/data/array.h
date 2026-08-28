#ifndef _wh_header_core_data_array_
#define _wh_header_core_data_array_

#include<wh-core/common.h>
#include<wh-posix/string.h>

#define WH_DARRAY(T, _name_, ...) \
    struct { \
        size_t size; \
        T* array; \
        __VA_ARGS__ \
    } _name_

#define WH_DARRAY_SIZE(_var_) \
    (_var_)->size

#define WH_DARRAY_VALUE(_var_, _index_) \
    (_var_)->array[_index_]

#define WH_DARRAY_CLEAR(_var_, _index_) \
    memset(&(_var_)->array[_index_], 0, sizeof((_var_)->array[_index_]))

#define WH_DARRAY_RESIZE(_var_, _count_, _func_) \
    (_var_)->array = (_func_((void*)((_var_)->array), &(_var_)->size, _count_, sizeof((_var_)->array[0])))

#endif /* _wh_header_core_data_array_ */

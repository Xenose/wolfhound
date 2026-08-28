#ifndef _wh_header_core_data_array_
#define _wh_header_core_data_array_

#include<wh-core/common.h>
#include<wh-posix/string.h>

#define WH_DARRAY(T, _name_) \
    struct { \
        size_t size; \
        T* array; \
    } _name_

#define WH_DARRAY_SIZE(_var_) \
    _var_->size

#define WH_DARRAY_VALUE(_var_, _index_) \
    _var_->array[index]

#define WH_DARRAY_CLEAR(_var_, _index_) \
    memser(&_var_->array[index], 0, sizeof(_var_->array[index]))

#define WH_DARRAY_RESIZE(_var_, _size_, _func_) \
    (_var_)->array = (_func_((void*)((_var_)->array), _size_, sizeof((_var_)->array[0])))

#endif /* _wh_header_core_data_array_ */

#ifndef _wh_header_common_macros_
#define _wh_header_common_macros_

#include <wh-posix/stddef.h>

#include <wh-core/os.h>
#include <wh-core/prefix.h>
#include <wh-core/c23-comp.h>

WH_C()

#define WH_PTR_MAX ((void*)-1)
#define WH_VA_ARGS(...) __VA_ARGS__

#define wh_ptr_assign(_ptr_, _value_) if (nullptr != _ptr_) *_ptr_ = _value_
#define wh_not(_x_) !(_x_)
#define wh_ptr_add(_ptr_, _x_) ((void*)(((char*)_ptr_) + _x_))
#define wh_ptr_sub(_ptr_, _x_) ((void*)(((char*)_ptr_) - _x_))

#define wh_ptr_offset(_ptr_, _x_) ((void*)&(((u8*)_ptr_)[_x_]))

#ifndef __FILENAME__
    #define __FILENAME__ __FILE__
#endif

// WH_EPF :: Empty Parameter Function
#if !(WH_SYSTEM&WH_SYS_GCC)&&!(WH_SYSTEM&WH_SYS_MINGW)&&!(WH_SYSTEM&WH_SYS_MSVC)&&!(WH_SYSTEM&WH_SYS_TCC)
    #define WH_EPF(x) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wmissing-field-initializers\"") \
        x \
        _Pragma("GCC diagnostic pop")
#else
    #define WH_EPF(x) \
        x
#endif

/* [MD_DOC]
 * wh_for is a macro for a for loop, it will go from 0
 * to the given end point.
 */
#define wh_for(_type_, _index_, _count_) for (_type_ _index_ = 0; (_index_) < (_count_); (_index_)++)

#define WH_INT(_x_) (int[]){ _x_ }
#define WH_UINT(_x_) (unsigned[]){ _x_ }

#define WH_I8(_x_) (i8[]){ _x_ }
#define WH_I16(_x_) (i16[]){ _x_ }
#define WH_I32(_x_) (i32[]){ _x_ }
#define WH_I64(_x_) (i64[]){ _x_ }

#define WH_U8(_x_) (u8[]){ _x_ }
#define WH_U16(_x_) (u16[]){ _x_ }
#define WH_U32(_x_) (u32[]){ _x_ }
#define WH_U64(_x_) (u64[]){ _x_ }


WH_C_END()
#endif /* _wh_header_common_macros_ */

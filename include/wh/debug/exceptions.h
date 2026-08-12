#ifndef _wh_header_debug_exceptions_
#define _wh_header_debug_exceptions_

#include<wh-posix/setjmp.h>
#include<wh-core/common.h>

enum {
    WH_EXCEPTION_SIGSEGV = -1,
};

typedef struct {
    struct_type sType;
    i64 error;
} wh_exception_s;

#if !(WH_SYSTEM&WH_SYS_POSIX)
    #define sigjmp_buf jmp_buf
    #define sigsetjmp(__env__, __val__) setjmp(__env__)
    #define siglongjmp(__env__, __val__) longjmp(__env__, __val__)
#endif

extern wh_thread i64 _jmp_index;

extern wh_thread i64 _jmp_error[];
extern wh_thread sigjmp_buf _jmp_buffers[];

extern i8 _jmp_init();

#define wh_try if (0 == _jmp_init()) for (i64 _old_index##__LINE__ = _jmp_index++; \
    _old_index##__LINE__ != _jmp_index; _jmp_index--) if (0 == (_jmp_error[_jmp_index] = sigsetjmp(_jmp_buffers[_jmp_index], 1)))

#define wh_catch(_ex_) else for (wh_exception_s _ex_ = (wh_exception_s){ .error = _jmp_error[_jmp_index] }; 0 != _ex_.error; _ex_.error = 0)

#define wh_throw(_error_) siglongjmp(_jmp_buffers[_jmp_index], _error_)

#endif /* _wh_header_debug_exceptions_ */

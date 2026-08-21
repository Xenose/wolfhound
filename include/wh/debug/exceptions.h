#ifndef _wh_header_debug_exceptions_
#define _wh_header_debug_exceptions_

#include<wh-posix/setjmp.h>
#include<wh-core/common.h>
#include<wh-posix/signal.h>

enum {
    WH_EXCEPTION_SIGSEGV = -2,
    WH_EXCEPTION_UNKNOWN = -1,

    WH_EXCEPTION_NONE = 0,
};

typedef struct {
    struct_type sType;
    i64 error;
} wh_exception_s;

typedef struct _wh_try_info {
    struct sigaction old_action;
    struct _wh_try_info* old_info;
    sigjmp_buf buffer;
    i64 error;
    i8 count;
} _wh_try_info_s;


extern i8 _jmp_init(_wh_try_info_s* info);
extern i8 _jmp_last_exception(wh_exception_s* exp);

#define wh_try for (_wh_try_info_s _info_##__LINE__ = { 0 }; \
        0 == _jmp_init(&_info_##__LINE__); ++_info_##__LINE__.count) \
        if (0 == sigsetjmp(_info_##__LINE__.buffer, 1))

#define wh_catch(type, name) else for (type name; WH_EXCEPTION_NONE == _jmp_last_exception(&name);)

// TODO  :: make a function to get last _wh_try_info_s
// #define wh_throw(_error_) siglongjmp(, _error_)

#endif /* _wh_header_debug_exceptions_ */

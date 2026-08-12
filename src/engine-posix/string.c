#include<wh-posix/errno.h>
#include<wh-posix/string.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    #include"_windows/string.c"
#elif (WH_SYSTEM&WH_SYS_POSIX)
    #include"_posix/string.c"
#endif

char* stpncpy_s(char* restrict dst, const char* restrict src, size_t length, int* error) {
    char* out = nullptr;

    if (nullptr == dst || nullptr == src) {
        if (nullptr != error) {
            *error = EINVAL;
        }
        goto go_error_exit;
    }

    out = stpncpy(dst, src, length);
go_error_exit:
    return out;
}

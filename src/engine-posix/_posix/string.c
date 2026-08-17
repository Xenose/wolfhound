#include<wh-posix/errno.h>
#include<wh-posix/string.h>

int strncpy_s(char* restrict dst, size_t dst_size, const char* restrict src, size_t src_size) {
    int error = 0;

    if (nullptr == dst) {
        error = EINVAL;
        goto go_error_exit;
    }

    if (0 == dst_size) {
        error = EINVAL;
        goto go_error_exit;
    }

    if (nullptr == src) {
        error = EINVAL;
        dst[0] = 0;
        goto go_error_exit;
    }

    if (_TRUNCATE == src_size) {
        src_size = strnlen(src, dst_size - 1);
        error = STRUNCATE;
    } else if (0 == src_size) {
        error = EINVAL;
        goto go_error_exit;
    } else if ((src_size + 1) > dst_size) {
        error = ERANGE;
        dst[0] = 0;
        goto go_error_exit;
    }

    memmove(dst, src, src_size);
    dst[src_size] = '\0';
go_error_exit:
    return error;
}



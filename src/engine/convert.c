#include<ctype.h>

#include<wh-maths/core.h>
#include<wh-maths/core.h>
#include<wh-posix/string.h>
#include<wh-sys/file.h>
#include<wh/convert.h>

char* _wh_uint2str(_wh_uint2str_params params) {
    const char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    u64 vl = params.value;
    u64 ln = (u64)wh_intpos(params.value, params.base);
    u64 pw = (u64)wh_intpow(ln, params.base);

    if (ln > params.buffer_length) {
        goto go_error_exit;
    }

    for (u64 i = 0; i <= ln; i++) {
        u64 tmp = vl / pw;
        vl -= tmp * pw;
        pw /= params.base;

        params.buffer[i] = table[tmp];
    }

go_error_exit:
    return params.buffer;
}

char* _wh_int2str(_wh_int2str_params params) {
    _wh_uint2str_params data = {
        .buffer = params.buffer,
        .buffer_length = params.buffer_length,
        .base = params.base
    };

    /*if (0 != params.buffer || 0 > params.buffer_length) {
      goto go_error_exit;
      }*/

    if (0 > params.value) {
        params.value = -params.value;
        *data.buffer = '-';
        ++data.buffer;
        --data.buffer_length;
    }

    data.value = wh_abs(params.value);
    return _wh_uint2str(data);
go_error_exit:
    return params.buffer;
}

i64 _wh_str2int(_wh_str2int_params params) {
    i64 out = 0;
    i64 sign = 1;

    switch (params.buffer[0]) {
        case '-':
            sign = -1;
        case '+':
            ++params.buffer;
            --params.buffer_length;
    }

    if ('0' <= params.buffer[0] && '9' >= params.buffer[0]) {
        out = params.buffer[0] - '0';

        for(u64 i = 1; i < params.buffer_length; i++) {
            if ('0' > params.buffer[i] || '9' < params.buffer[i]) {
                break;
            }

            out *= 10;
            out += params.buffer[i] - '0';
        }
    }

    return out * sign;
}

char* float2str(float value, char* buffer, u64 buffer_length) {
    struct {
        u64 s : 1;
        u64 r : 8;
        u64 d : 23;
    }* f = ((void*)&value);

    if (0 == f->d && 255 == f->r) {
        strncpy_s(buffer, buffer_length, "NaN", 3);
    }

    return nullptr;
}

void _wh_str_invert(_wh_str_invert_params params) {
    wh_for(i64, i, params.length) {
        switch (params.buffer[i]) {
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
            case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
            case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z':
                params.buffer[i] = (char)toupper(params.buffer[i]);
                break;
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
            case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
            case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z':
                params.buffer[i] = (char)toupper(params.buffer[i]);
                break;
        }
    }
}

const char* _wh_filetype2str(_wh_filetype2str_params params) {
    switch (params.type_id) {
        case WH_STRUCT_TYPE_IMG_PNG:
            return "WH_STRUCT_FILE_TYPE_PNG";
    }

    return "WH_FILE_TYPE_UNKNOWN";
}

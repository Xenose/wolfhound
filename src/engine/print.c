
// tmp for debug
#include<wh-posix/stdio.h>
#include<wh-posix/errno.h>

#include<wh-posix/stdarg.h>
#include<wh-posix/stdatomic.h>
#include<wh-posix/string.h>
#include<wh-posix/time.h>
#include<wh-posix/unistd.h>
#include<wh-sys/atomic_lock.h>
#include<wh-sys/memreq.h>
#include<wh/convert.h>
#include<wh/data/hashmap.h>
#include<wh/debug/error.h>
#include<wh/maths/core.h>
#include<wh/print.h>

// =======================================================================================================
// Globals
// =======================================================================================================
#if !(WH_SYSTEM&WH_SYS_TCC)
static wh_thread char _buffer[8096];
#endif

// i64 (*func)(wh_print_data_s* data, void* ptr);
static wh_hashmap_s _map = {
    .stype = WH_STRUCT_TYPE_HASHMAP_LAZY_PTR_SYS,
    .slots = nullptr,
    .type_size = sizeof(void*),
    .resize_size = 8096,
};

// =======================================================================================================
// pre defining
// =======================================================================================================
static void _wh_print_format(wh_print_data_s* data, va_list list);

// =======================================================================================================
// private function start
// =======================================================================================================

void _wh_print_add_func(_wh_print_add_func_params params) {
    wh_hashmap_insert(&_map, (void*)params.key,  (void*)params.func);
}

// =======================================================================================================
// private formatting function start
// =======================================================================================================
static void _wh_print_call_func(wh_print_data_s* data, void* ptr, char* key_start, char* key_end) {
    i64 (*func)(wh_print_data_s* data, void* ptr) = (i64(*)(wh_print_data_s*, void*))wh_hashmap_get(&_map, key_start);

    if (nullptr != func) {
        func(data, ptr);
    }

    data->format = key_end + 2;
}

static void _wh_print_cpychar(wh_print_data_s* d, char c) {
    if (-1 == wh_print_buffer_check(d, 1)) {
        return;
    }

    d->buffer[0] = c;
    ++d->buffer;
    ++d->format;
}

// TODO replace with something faster.
static void _wh_print_fstr_slow(wh_print_data_s* d, char type, double value) {
    char out[64];
    char* format = "%.*f";
    int precision = d->print_format.flags.length_set ? (int)d->print_format.right : 6;
    int length = 0;

                //case 'a': case 'A': case 'e': case 'E': case 'f': case 'F': case 'g': case 'G':
    switch (type) {
        case 'a': format = "%.*a"; break;
        case 'A': format = "%.*A"; break;
        case 'e': format = "%.*e"; break;
        case 'E': format = "%.*E"; break;
        case 'g': format = "%.*g"; break;
        case 'G': format = "%.*G"; break;
    }
    
    length = snprintf(out, sizeof(out), format, precision, value);

    if (length < 0 || length >= (int)sizeof(out)) {
        return;
    }

    if (-1 == wh_print_buffer_check(d, (u64)length)) {
        return;
    }

    memcpy(d->buffer, out, (unsigned)length);
    d->buffer += length;
    ++d->format;
}

static void _wh_print_cpystr(wh_print_data_s* d, char* tmp, i64 length) {
    i64 padding = 0;

    if (nullptr == tmp) {
        tmp = (char*)"%NULL%";
        length = 6;
    } else if (0 == length) {
        length = (i64)strlen(tmp);
    }

    if (d->print_format.flags.length_set) {
        length = (i64)d->print_format.right > length ? length : (i64)d->print_format.right;
    }

    padding = (i64)d->print_format.left > length ? (i64)d->print_format.left - length : 0;

    if (-1 == wh_print_buffer_check(d, (u64)(length + padding))) {
        goto go_error_exit;
    }

    if (d->print_format.flags.left_align) {
        memcpy(d->buffer, tmp, (u64)length);

        if (d->print_format.flags.alt_form) {
            wh_str_invert(d->buffer, (u64)length);
        }

        d->buffer += length;

        memset(d->buffer, ' ', (u64)padding);
        d->buffer += padding;
    } else {
        memset(d->buffer, ' ', (u64)padding);
        d->buffer += padding;

        memcpy(d->buffer, tmp, (u64)length);

        if (d->print_format.flags.alt_form) {
            wh_str_invert(d->buffer, (u64)length);
        }

        d->buffer += length;
    }

go_error_exit:
    ++d->format;
}


static void _wh_print_uint(wh_print_data_s* d, u64 value, u64 base) {
    u64 length = wh_uintpos(value, base) + (0 > value ? 2 : 1);

    if (-1 == wh_print_buffer_check(d, length)) {
        return;
    }

    wh_uint2str(value, d->buffer, length, base);
    d->buffer += length;
    ++d->format;
}

static void _wh_print_int(wh_print_data_s* d, i64 value, i64 base) {
    i64 length = wh_intpos(value, base) + (0 > value ? 2 : 1);

    if (-1 == wh_print_buffer_check(d, (u64)length)) {
        return;
    }

    wh_int2str(value, d->buffer, (u64)length, (u64)base);
    d->buffer += length;
    ++d->format;
}

static void _wh_print_int128(wh_print_data_s* d, i128 value, i64 base) {
    i128 length = wh_intpos128(value, base) + (0 > value ? 2 : 1);

    if (-1 == wh_print_buffer_check(d, (u64)length)) {
        return;
    }

    wh_int2str128(value, d->buffer, (u64)length, (u64)base);
    d->buffer += length;
    ++d->format;
}

static void _wh_print_int_bytes(wh_print_data_s* d, i64 value, i64 base) {
    const char* end = "B";

    if (value >= WH_1GB) {
        end = "GB";
        value /= WH_1GB;
    } else if (value >= WH_1MB) {
        end = "MB";
        value /= WH_1MB;
    } else if (value >= WH_1KB) {
        end = "KB";
        value /= WH_1KB;
    }

    _wh_print_int(d, value, base);
    d->buffer += stpcpy(d->buffer, end) - d->buffer;
    ++d->format;
}

static void _wh_print_memory(wh_print_data_s* data, u8* ptr, int bytes) {
    i64 length = 0;

    if (-1 == wh_print_buffer_check(data, (u64)bytes * 4)) {
        return;
    }

    wh_for(i64, i, bytes) {
        length = wh_intpos(ptr[i], 16) + 1;

        if (!(i % 8)) {
            data->buffer[0] = '\n';
            data->buffer[1] = '\t';
            data->buffer[2] = ' ';
            data->buffer += 3;
        } else {
            data->buffer[0] = ' ';
            ++data->buffer;
        }

        switch (length) {
            case 1:
                *data->buffer = '0';
                ++data->buffer;
            case 2:
                wh_int2str(ptr[i], data->buffer, (u64)length, 16);
                data->buffer += length;
        }
    }

    ++data->format;
}

static void _wh_print_time(wh_print_data_s* data, char* const format) {
    struct tm* tm = nullptr;
    char buffer[256] = { 0 };
    u64 length = 0;
    time_t t = { 0 };

    t = time(NULL);
    tm = localtime(&t);
    length = strftime(buffer, 255, format, tm);

    if (-1 == wh_print_buffer_check(data, (u64)length)) {
        return;
    }

    memcpy(data->buffer, buffer, length);

    data->buffer += length;
    ++data->format;
}

static void _wh_print_format_sub(wh_print_data_s* data, va_list list) {
    char* f = data->format;

    if (nullptr != (data->format = va_arg(list, char*))) {
        _wh_print_format(data, list);
    }

    data->format = f + 1;
}


// =======================================================================================================
// private formatting loop function start
// =======================================================================================================

// I don't like this but it reduces code duplication.
#define _WH_PRINT_FORMAT_COMMON_CASE(_goto_, _formater_, _data_) \
    case (_formater_): \
        goto _goto_; \
    case '#': \
        (_data_)->print_format.flags.alt_form = true; \
        goto _goto_; \
    case '-': \
        (_data_)->print_format.flags.left_align = true; \
        goto _goto_; \
    case '+': \
        (_data_)->print_format.flags.force_sign = true; \
        goto _goto_; \
    case ' ': \
        (_data_)->print_format.flags.space_pad = true; \
        goto _goto_; \
    case '0': \
        (_data_)->print_format.flags.zero_pad = true; \
        goto _goto_; \
    case '.': \
        vp = &(_data_)->print_format.right; \
        (_data_)->print_format.flags.length_set = true; \
        ++(_data_)->format; \
        goto _goto_; \
    case '1': case '2': case '3': case '4': case '5': \
    case '6': case '7': case '8': case '9': \
        *vp = (u64)wh_str2int((_data_)->format, (i64)strlen((_data_)->format), 10); \
        vp = &(_data_)->print_format.left; \
        (_data_)->format += wh_uintpos(*vp); \
        goto _goto_; \
    case 'l': \
        if ((_data_)->print_format.flags.long_value) { \
            (_data_)->print_format.flags.llong_value = true; \
        } else { \
            (_data_)->print_format.flags.long_value = true; \
        } \
        ++(_data_)->format; \
        goto _goto_


static void _wh_print_format(wh_print_data_s* data, va_list list) {
    void* tmp = nullptr;
    u64* vp = &data->print_format.left;

    goto go_loop; // skipping the memset
go_loop_memset:
    memset(&data->print_format, 0, sizeof(wh_print_format_s));
go_loop:
    switch (*data->format) {
        case '\0':
            // time to break and leave this loop
            break;

        case '$': // custom cases
go_dollar_switch:
            switch (*(++data->format)) {
                _WH_PRINT_FORMAT_COMMON_CASE(go_dollar_switch, '$', data);

                case '[': // custom function from user using hash maps
                    _wh_print_call_func(data, va_arg(list, void*), data->format + 1, strstr(data->format, "]"));
                    break;
                case 'f':
                    _wh_print_format_sub(data, list);
                    break;
                case 'F': // converts file type to string
                    _wh_print_cpystr(data, (char*)wh_filetype2str(va_arg(list, i64)), 0);
                    break;
                case 'n':
                    _wh_print_cpystr(data, (char*)wh_errno_str(va_arg(list, i64)), 0);
                    break;
                case 'k':
                    _wh_print_int_bytes(data, va_arg(list, i64), 10);
                    break;
                case 'm': // memory
                    tmp = va_arg(list, u8*);
                    _wh_print_memory(data, tmp, va_arg(list, int));
                    break;
                case 's': // string with length
                    tmp = va_arg(list, char*);
                    _wh_print_cpystr(data, tmp, va_arg(list, i64));
                    break;
                case 't': // time with format $t
                    _wh_print_time(data, va_arg(list, char*));
                    break;
                case 'v': // vk result
                    _wh_print_cpystr(data, (char*)wh_vk_status_str(va_arg(list, i64)), 0);
                    break;
            }

            goto go_loop_memset;

        case '%': // standard cases
go_standard_switch:
            switch (*(++data->format)) {
                _WH_PRINT_FORMAT_COMMON_CASE(go_standard_switch, '%', data);
                
                case 'c':
                    _wh_print_cpychar(data, (char)va_arg(list, int));
                    break;

                case 'a': case 'A': case 'e': case 'E': case 'f': case 'F': case 'g': case 'G':
                    _wh_print_fstr_slow(data, *data->format, va_arg(list, double));
                    break;

                case 'b':
                    if (data->print_format.flags.alt_form) {
                        data->print_format.flags.alt_form = false;
                        _wh_print_cpystr(data, "0b", 2);
                        data->format--;
                    }

                    _wh_print_uint(data, va_arg(list, u64), 2);
                    break;

                case 'd': case 'i':
                    if (data->print_format.flags.llong_value) {
                        _wh_print_int128(data, va_arg(list, i128), 10);
                    } else if (data->print_format.flags.long_value) {
                        _wh_print_int(data, va_arg(list, i64), 10);
                    } else {
                        _wh_print_int(data, va_arg(list, int), 10);
                    }
                    break;


                case 'u':
                    _wh_print_uint(data, va_arg(list, u64), 10);
                    break;

                case 's':
                    _wh_print_cpystr(data, va_arg(list, char*), 0);
                    break;

                case 'm':
                    _wh_print_cpystr(data, (char*)wh_errno_str(errno), 0);
                    break;

                case 'n':
                    tmp = ((void*)va_arg(list, int*)); 

                    if (nullptr != tmp) {
                        *((int*)tmp) = (int)(data->written + (int)(data->buffer - data->start));
                    }

                    break;

                case 'o':
                    _wh_print_int(data, va_arg(list, u64), 8);
                    break;

                case 'p':
                    _wh_print_cpystr(data, "0x", 2);
                    data->format--;
                    _wh_print_uint(data, va_arg(list, uintptr_t), 16);
                    break;

                case 'x':
                    _wh_print_cpystr(data, "0x", 2);
                    goto go_X;
                case 'X':
                    _wh_print_cpystr(data, "0x", 2);
go_X:
                    data->format--;
                    _wh_print_uint(data, va_arg(list, u64), 16);
                    break;
            }

            goto go_loop_memset;

go_default:
        default:
            _wh_print_cpychar(data, *data->format);
            goto go_loop;
    }
}

// =======================================================================================================
// Non static functions
// =======================================================================================================

i64 _wh_print_buffer_check(_wh_print_buffer_check_params params) {
    i64 ret = 0;
    i64 rem = &params.data->start[params.data->length]
        - (params.data->buffer + params.needed + 10);

    if (0 >= rem) {
        ret = write((int)params.data->fd, params.data->start,
                (size_t)(params.data->buffer - params.data->start));

        if (-1 == ret) {
            goto go_error_exit;
        }

        params.data->written += ret;
        params.data->buffer = params.data->start;
    }

go_error_exit:
    return ret;
}

i64 _wh_print_va(_wh_print_params params, va_list list) {
#if (WH_SYSTEM&WH_SYS_TCC)
    char _buffer[8096];
#endif

    i64 ret = 0;
    char* buffer = params.buffer;

    if (nullptr == params.buffer) {
        buffer = _buffer;
        params.buffer_length = 8096;
    }

    if (nullptr == params.format) {
        params.format = "%%NULL%%";
    }

    if (0 == params.fd) {
        params.fd = 1;
    }

    wh_print_data_s data = {
        buffer,
        (char*)params.format,
        buffer,
        params.buffer_length,
        0,
        params.fd,
        { 0 }
    };

    data.buffer += params.offset;
    _wh_print_format(&data, list);

    if (WH_PRINT_ADD_NEW_LINE & params.flags) {
        _wh_print_cpychar(&data, '\n');
    }

    if (WH_PRINT_NO_FLUSH & params.flags) {
        ret = data.buffer - data.start;
        goto go_exit;
    }

    ret = write((int)data.fd, data.start, (size_t)(data.buffer - data.start));

    if (-1 != ret) {
        ret += data.written;
    }

go_exit:
    return ret;
}

i64 _wh_print(_wh_print_params params, ...) {
    i64 ret = 0;
    va_list list;

    va_start(list, params);
    ret = _wh_print_va(params, list);
    va_end(list);

    return ret;
}

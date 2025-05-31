#include<stdarg.h>
#include<stdatomic.h>
#include<ctype.h>

// tmp for debug
#include<stdio.h>
#include<errno.h>

#include<wh/wrap/unistd.h>
#include<wh/wrap/string.h>

#include<wh/convert.h>
#include<wh/memory.h>
#include<wh/error.h>
#include<wh/print.h>
#include<wh/maths.h>

// =======================================================================================================
// Struct declerations 
// =======================================================================================================
typedef struct {
	char key[32];
	i64 (*func)(wh_print_data_s* data, void* ptr);
} _hw_print_func;

typedef struct {
	atomic_int_least64_t count;
	atomic_int_least64_t slots;
	_Atomic(_Atomic(_hw_print_func)*) table;
} _hw_print_func_table;

// =======================================================================================================
// Globals
// =======================================================================================================
static wh_thread char _buffer[8096];
static _hw_print_func_table _wh_func_table = { 0 };

// =======================================================================================================
// pre defining
// =======================================================================================================
static void _wh_print_format(wh_print_data_s* data, va_list list);

// =======================================================================================================
// private function start
// =======================================================================================================

static void _wh_print_call_func(wh_print_data_s* data, void* ptr, char* key_start, char* key_end) {
	i64 (*func)(wh_print_data_s* data, void* ptr) = NULL;
	i64 key = 0;

	if (NULL == key_end) {
		goto go_error_exit_no_end_key;
	}

	key = wh_hash_simple(key_start, atomic_load(&_wh_func_table.slots), key_end - key_start);

	if (-1 == key) {
		goto go_error_exit;
	}
	
	//func = atomic_load(&atomic_load(&_wh_func_table.table)[key]).func;

	if (NULL != func) {
		func(data, ptr);
	}

go_error_exit:
	data->format = key_end + 2;
go_error_exit_no_end_key:
	return;
}

static void _wh_print_cpychar(wh_print_data_s* d, char c) {
	i64 written = wh_print_buffer_check(d, 1);

	if (-1 == written) {
		return;
	}

	d->buffer[0] = c;
	++d->buffer;
	++d->format;
}

static void _wh_print_cpystr(wh_print_data_s* d, char* tmp, i64 length) {
	i64 written = 0;
	i64 padding = 0;

	if (NULL == tmp) {
		tmp = (char*)"%NULL%";
		length = 6;
	} else if (0 == length) {
		length = strlen(tmp);
	}

	if (d->print_format.flags.length_set) {
		length =  d->print_format.right > length ? length : d->print_format.right;
	}

	padding = d->print_format.left > length ? d->print_format.left - length : 0;

	if (-1 == (written = wh_print_buffer_check(d, length + padding))) {
		goto go_error_exit;
	}

	if (d->print_format.flags.left_align) {
		memcpy(d->buffer, tmp, length);

		if (d->print_format.flags.alt_form) {
			wh_str_invert(d->buffer, length);
		}

		d->buffer += length;

		memset(d->buffer, ' ', padding);
		d->buffer += padding;
	} else {
		memset(d->buffer, ' ', padding);
		d->buffer += padding;

		memcpy(d->buffer, tmp, length);

		if (d->print_format.flags.alt_form) {
			wh_str_invert(d->buffer, length);
		}

		d->buffer += length;
	}

go_error_exit:
	++d->format;
}

static void _wh_print_uint(wh_print_data_s* d, i64 value, i64 base) {
	i64 written = 0;
	i64 length = wh_intlog(value, base) + (0 > value ? 2 : 1);

	written = wh_print_buffer_check(d, length);

	if (-1 == written) {
		return;
	}

	wh_uint2str(value, d->buffer, length, 10);
	d->buffer += length;
	++d->format;
}

static void _wh_print_int_bytes(wh_print_data_s* d, i64 value, i64 base) {
	const char* end = "B";
	i64 written = 0;
	i64 length = 0;

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

	length = wh_intlog(value, base) + (0 > value ? 2 : 1);
	written = wh_print_buffer_check(d, length + 2);

	if (-1 == written) {
		return;
	}

	wh_int2str(value, d->buffer, length, base);
	d->buffer += length;
	d->buffer += stpcpy(d->buffer, end) - d->buffer;
	++d->format;
}

static void _wh_print_int(wh_print_data_s* d, i64 value, i64 base) {
	i64 written = 0;
	i64 length = wh_intlog(value, base) + (0 > value ? 2 : 1);

	written = wh_print_buffer_check(d, length);

	if (-1 == written) {
		return;
	}

	wh_int2str(value, d->buffer, length, base);
	d->buffer += length;
	++d->format;
}

static void _wh_print_format_sub(wh_print_data_s* data, va_list list) {
	char* f = data->format;

	if (NULL != (data->format = va_arg(list, char*))) {
		_wh_print_format(data, list);
	}

	data->format = f + 1;
}

static void _wh_print_format(wh_print_data_s* data, va_list list) {
	u64* vp = &data->print_format.left;

go_loop:
	switch (*data->format) {
		// time to break
		case '\0':
			break;

		// custom cases
		case '$':
		go_dollar_switch:
			switch (*(++data->format)) {
				case '$':
					goto go_default;
				case '#':
					data->print_format.flags.alt_form = true;
					goto go_dollar_switch;
				case '-':
					data->print_format.flags.left_align = true;
					goto go_dollar_switch;
				case '+':
					data->print_format.flags.force_sign = true;
					goto go_dollar_switch;
				case ' ':
					data->print_format.flags.space_pad = true;
					goto go_dollar_switch;
				case '0':
					data->print_format.flags.zero_pad = true;
					goto go_dollar_switch;
				case '.':
					vp = &data->print_format.right;
					data->print_format.flags.length_set = true;
					++data->format;
				case '1': case '2': case '3': case '4': case '5': 
				case '6': case '7': case '8': case '9':
					*vp = wh_str2int(data->format, strlen(data->format), 10); 
					vp = &data->print_format.left;
					goto go_dollar_switch;
				case '[': // custom function from user using hash maps
					_wh_print_call_func(data, va_arg(list, void*), data->format + 1, strstr(data->format, "]") - 1);
					break;
				case 'b': // binary
					break;
				case 'f':
					_wh_print_format_sub(data, list);
					break;
				case 'n':
					_wh_print_cpystr(data, (char*)wh_errno_str(va_arg(list, i64)), 0);
					break;
				case 'k':
					_wh_print_int_bytes(data, va_arg(list, i64), 10);
					break;
				case 'l':
					data->print_format.flags.space_pad = true;
					break;
				case 'm': // memory
					break;
				case 's': // string with length
					_wh_print_cpystr(data, va_arg(list, char*), va_arg(list, u64));
					break;
				case 't': // time with format $t[]
					break;
				case 'v': // vk result
					_wh_print_cpystr(data, (char*)wh_vk_status_str(va_arg(list, i64)), 0);
					break;
			}
			
			memset(&data->print_format, 0, sizeof(wh_print_format_s));
			goto go_loop;

		// standard cases
		case '%':
		go_standard_switch:
			switch (*(++data->format)) {
				case '%':
					goto go_default;
				case '#':
					data->print_format.flags.alt_form = true;
					goto go_standard_switch;
				case '-':
					data->print_format.flags.left_align = true;
					goto go_standard_switch;
				case '+':
					data->print_format.flags.force_sign = true;
					goto go_standard_switch;
				case ' ':
					data->print_format.flags.space_pad = true;
					goto go_standard_switch;
				case '0':
					data->print_format.flags.zero_pad = true;
					goto go_standard_switch;
				case '.':
					vp = &data->print_format.right;
					data->print_format.flags.length_set = true;
					++data->format;
				case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
					*vp = wh_str2int(data->format, strlen(data->format), 10); 
					vp = &data->print_format.left;
					goto go_standard_switch;
				case 'a':
				case 'A':
				case 'c':
					_wh_print_cpychar(data, va_arg(list, int));
					break;
				case 'd':
					goto go_print_int;
				case 'e':
				case 'E':
				case 'f':
					va_arg(list, double);
					break;
				case 'g':
				case 'G':
go_print_int:
				case 'i':
					if (data->print_format.flags.llong_value) {
						_wh_print_int(data, va_arg(list, i128), 10);
					} else if (data->print_format.flags.long_value) {
						_wh_print_int(data, va_arg(list, i64), 10);
					} else {
						_wh_print_int(data, va_arg(list, int), 10);
					}
					break;
				case 'l':
					if (data->print_format.flags.long_value) {
						data->print_format.flags.llong_value = true;
					} else {
						data->print_format.flags.long_value = true;
					}
					++data->format;
					goto go_standard_switch;
				case 'u':
					_wh_print_uint(data, va_arg(list, u64), 10);
					break;
				case 's':
					_wh_print_cpystr(data, va_arg(list, char*), 0);
					break;
				case 'm':
					_wh_print_cpystr(data, (char*)wh_errno_str(errno), 0);
					break;
				case 'o':
					_wh_print_int(data, va_arg(list, i64), 8);
					break;
				case 'p':
					_wh_print_cpystr(data, "0x", 2);
					data->format--;
					_wh_print_uint(data, va_arg(list, u64), 16);
					break;
				case 'x':
				case 'X':
					_wh_print_cpystr(data, "0x", 2);
					data->format--;
					_wh_print_int(data, va_arg(list, i64), 16);
					break;
			}
			
			memset(&data->print_format, 0, sizeof(wh_print_format_s));
			goto go_loop;

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
		ret = write(params.data->fd, params.data->start,
				  params.data->buffer - params.data->start);
		
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
	i64 ret = 0;
	char* buffer = params.buffer;

	if (NULL == params.buffer) {
		buffer = _buffer;
		params.buffer_length = 8096;
	}

	wh_print_data_s data = {
		buffer,
		(char*)params.format,
		buffer,
		params.buffer_length,
		0,
		params.fd
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
		
	ret = write(data.fd, data.start, data.buffer - data.start);

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

void _wh_print_add_func(_wh_print_add_func_params params) {
	i64 key = 0;

	if (0 == atomic_load(&_wh_func_table.slots)) {
		//atomic_store(&_wh_func_table.table, wh_mem(sizeof(void*) * 16, .flags = WH_MEM_ZERO));
		//atomic_store(&_wh_func_table.slots, 16);

		if (NULL == atomic_load(&_wh_func_table.table)) {
			// TODO handle error
		}
	}

	key = wh_hash_simple(params.key, atomic_load(&_wh_func_table.slots));

	if (NULL != params.func) {
		if (NULL != &atomic_load(&_wh_func_table.table)[key]) {
			// TODO resize array and handle moving of pointer
			key = wh_hash_simple(params.key, atomic_load(&_wh_func_table.slots));
		}
	
		//atomic_store(&(_wh_func_table.table[key]), (_hw_print_func) { .func = params.func } );
		//atomic_fetch_add(&_wh_func_table.count, 1);
	}
}

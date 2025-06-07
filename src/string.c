#include<stdarg.h>
#include<string.h>

#include<wh/string.h>
#include<wh/memory.h>
#include<wh/debug.h>

char* _wh_strcat(_wh_strcat_params params, ...) {
	const char* s = nullptr;
	u64 sl = 0; // string length
	u64 len = params.buffer_length;
	va_list list;

	if (0 == params.buffer_length || nullptr == params.buffer) {
		goto go_exit;
	}

	params.buffer += params.offset;
	len -= params.offset;

	va_start(list, params);

	while(nullptr != (s = va_arg(list, const char*))) {
		sl = strlen(s);

		if (len < sl) {
			memcpy(params.buffer, s, len);
			params.buffer += len;
			break;
		}

		memcpy(params.buffer, s, sl);
		params.buffer += sl;
		len -= sl;
	}

	va_end(list);
go_exit:
	return params.buffer;
}

wh_string_s _wh_string_append(_wh_string_append_params, ...) {
	return (wh_string_s) {};
}

wh_string_s _wh_string_create(int dummy, ...) {
	va_list args;
	wh_string_s out = { 0 };
	void* tmp = nullptr;
	char* str = nullptr;
	u64 length = 0;

	va_start(args, dummy);

	while (nullptr != (str = va_arg(args, char*))) {
		length = strlen(str);

		tmp = wh_mem(out.length + length, out.str);

		if (nullptr == tmp) {
			wh_log_warning(("Failed to append string!"));
			break;
		}

		out.str = tmp;
		memcpy(&out.str[out.length], str, length);
		out.length += length;
	}


	if (0 != out.length) {
		tmp = wh_mem(out.length + 1, out.str);

		if (nullptr == tmp) {
			wh_log_critical(("wh_mem failed to realloc memory for string!"));
			goto go_exit_error;
		}

		out.str = tmp;
		out.str[out.length] = '\0';
	}

go_exit_error:
	va_end(args);
	return out;
}

const char* _wh_strstr(_wh_strstr_params params) {
	const char* value = nullptr;

	if (nullptr == params.key || nullptr == params.str) {
		if (nullptr != params.error) {
			*params.error = WH_ERROR_INVALID_PARAM_NULLPTR;
		}
		goto go_error_exit;
	}

	params.key_length = 0 == params.key_length ? 
		strlen(params.key) : params.key_length;
	params.str_length = 0 == params.str_length ?
		strlen(params.str) : params.str_length;

	if (params.key_length > params.str_length) {
		if (nullptr != params.error) {
			*params.error = WH_ERROR_NO_MATCH;
		}
		goto go_error_exit;
	}

	wh_for(u64, i, (params.str_length - params.key_length) + 1) {
		if (!memcmp(params.key, &params.str[i], params.key_length)) {
			value = &params.str[i];
			goto go_found;
		}
	}

go_error_exit:
go_found:
	return value;
}

#include<errno.h>
#include<wh/wrap/string.h>

#ifdef _WIN32

char* stpncpy(char* restrict dst, const char* restrict src, size_t length) {
	size_t l = strlen(src);
	l = l < length ? l : length;

	memset(&dst[l], 0, length - l);
	return wh_ptr_add(memmove(dst, src, l), l); // <--- dst + l
}

char* stpcpy(char* restrict dst, const char* restrict src) {
	size_t l = strlen(src);
	return wh_ptr_add(memmove(dst, src, l), l); // <--- dst + l
}

#elif defined(__linux__)

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

	if (WH_TRUNCATE == src_size) {
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

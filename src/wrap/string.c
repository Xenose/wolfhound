#include<wh/wrap/string.h>

#ifdef _WIN32

char* stpncpy(char* restrict dst, const char* restrict src, size_t length) {
	size_t l = strlen(src);
	l = l < length ? l : length;

	memset(&dst[l], 0, length - l);
	return memmove(dst, src, l) + l; // <--- dst + l
}

char* stpcpy(char* restrict dst, const char* restrict src) {
	return stpncpy(dst, src, strlen(src) + 1);
}

#endif

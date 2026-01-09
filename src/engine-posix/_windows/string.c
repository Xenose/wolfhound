#include<wh-posix/string.h>

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



#include<wh/wrap/string.h>

#ifdef _WIN32

char* stpncpy(char* restrict dst, const char* restrict src, size_t length) {
	int l = strlen(src);
	l = l < length ? l : length;

	return memmove(dst, src, l) + l;
}

char* stpcpy(char* restrict dst, const char* restrict src) {
	return stpncpy(dst, src, strlen(src));
}

#endif

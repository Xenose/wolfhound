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

void* memccpy(void* restrict dst, const void* restrict src, int c, size_t n) {
	u8* d = dst;
	u8* s = (u8*)src;
	size_t i = 0;

	for (; i < n; i++) {
		d[i] = s[i];

		if ((u8)c == d[i]) {
			return (void*)&d[i + 1];
		}
	}

	return nullptr;
}

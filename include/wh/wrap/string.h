#ifndef _wh_header_wrap_string_
#define _wh_header_wrap_string_

#include<stddef.h>
#include<string.h>
#include<wh/common.h>

#ifdef _WIN32

#define WH_TRUNCATE _TRUNCATE

extern char* stpncpy(char* restrict dst, const char* restrict src, size_t length);
extern char* stpcpy(char* restrict dst, const char* restrict src);

#else

#define WH_TRUNCATE (size_t)(-1)

extern int strncpy_s(char* restrict dst, size_t dst_size, const char* restrict src, size_t src_size);

#endif

#endif /* _wh_header_wrap_string_ */

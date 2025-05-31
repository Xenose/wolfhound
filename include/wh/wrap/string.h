#ifndef _wh_header_wrap_string_
#define _wh_header_wrap_string_

#include<stddef.h>
#include<string.h>

#ifdef _WIN32
extern char* stpncpy(char* restrict dst, const char* restrict src, size_t length);
extern char* stpcpy(char* restrict dst, const char* restrict src);
#endif

#endif /* _wh_header_wrap_string_ */

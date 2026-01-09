#ifndef _wh_header_wrap_string_
#define _wh_header_wrap_string_

#include<stddef.h>
#include<string.h>
#include<wh/common.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)

#define WH_TRUNCATE _TRUNCATE

extern char* stpncpy(char* restrict dst, const char* restrict src, size_t length);
extern char* stpcpy(char* restrict dst, const char* restrict src);

#else

#define WH_TRUNCATE (size_t)(-1)

extern int strncpy_s(char* restrict dst, size_t dst_size, const char* restrict src, size_t src_size);

#endif

#ifndef WH_SHOTGUN_FOOT_OH_YEA
	#define strcat(...) static_assert(0, "DO NOT USE STRCAT USE WH_STRCAT"); strcat(__VA_ARGS__)
#else
	#warning YOU ARE ABOUT TO SHOT YOURSELF!
#endif /* WH_SHOTGUN_FOOT_OH_YEA */

#endif /* _wh_header_wrap_string_ */

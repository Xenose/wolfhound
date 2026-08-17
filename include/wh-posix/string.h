#ifndef _wh_header_wrap_string_
#define _wh_header_wrap_string_

#include<wh-posix/stddef.h>
#include<wh-core/common.h>
#include<string.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
    extern char* stpncpy(char* restrict dst, const char* restrict src, size_t length);
    extern char* stpcpy(char* restrict dst, const char* restrict src);

    /* [MD_DOC]
     *
     * # Summary memccpy(void* restrict dst, const void* restrict src, int c, size_t n)
     *
     * I will write down this for future reference as the man-page is horrible,
     * the memccpy function copies until n(bytes) is reached or the first character(c) is
     * hit/encountered.
     *
     * If the pointers are pointing to the same memory region the behavior is undefined.
     *
     * ## Return
     * If the char(c) was not found in the scope of n(bytes) then NULL is returned,
     * otherwise if it was found then dst will be returned after the found character.
     *
     * ## Notes
     * Posix doesn't say what happens if src or dst is nullptr's...
     */
    extern void* memccpy(void* restrict dst, const void* restrict src, int c, size_t n);
#else

    #define _TRUNCATE (size_t)(-1)
    extern int strncpy_s(char* restrict dst, size_t dst_size, const char* restrict src, size_t src_size);
#endif

#ifndef WH_SHOTGUN_FOOT_OH_YEA
    #define strcat(...) static_assert(0, "DO NOT USE STRCAT USE WH_STRCAT"); strcat(__VA_ARGS__)
#else
    #warning YOU ARE ABOUT TO SHOT YOURSELF!
#endif /* WH_SHOTGUN_FOOT_OH_YEA */

#endif /* _wh_header_wrap_string_ */

#ifndef _wh_header_wrap_unistd_
#define _wh_header_wrap_unistd_

#include<wh/common.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<unistd.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#include<wh-posix/windows.h>

	#define write _write

	extern int getpagesize(void);

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
#endif

#ifndef _GNU_SOURCE
	extern pid_t gettid(void);
#endif

#endif /* _wh_header_wrap_unistd_ */

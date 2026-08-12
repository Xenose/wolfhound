#ifndef _wh_header_common_c23_comp_
#define _wh_header_common_c23_comp_

#include <wh-posix/stdint.h>
#include <wh-core/os.h>

/*
 * C23 has added the keyword nullptr to the language,
 * so we should use the more type safe version when possible.
 */
#if !defined(__cplusplus)
    #if !defined(nullptr) && (__STDC_VERSION__ < 202311L)
        #define nullptr NULL
    #endif
#endif

/*
 * C23 support the new keyword __VA_OPT__ but some
 * compilers will need to fallback to the older GNU
 * extension.
 */
#if (WH_SYSTEM&WH_SYS_TCC)
    #define WH_VA_OPT(...) , ##__VA_ARGS__
#else
    #define WH_VA_OPT(...) __VA_OPT__(,) __VA_ARGS__
#endif

/*
 * After C11 it seems like there is a keyword
 * wolfhound is built for C23, but this macro
 * cost me nothing so I would say its worth
 * the extra macro.
 */
#if (WH_SYSTEM&WH_SYS_MSVC)
    #define wh_thread __declspec(thread)
// #elif (WH_SYSTEM&WH_SYS_TCC)
//    #define wh_thread // TODO assert once we solve this...
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define wh_thread _Thread_local
#else
    #define wh_thread __thread
#endif

// TCC atomic concept
/* Proof of concept
 *
 * #define T* get_value(wh_thread_local_data* data) { \
 *	void* tmp = nullptr; \
 *	pid_t lt = getpid(); \
 *	\
 *	for (i64 i = 0; i < data.count; i++) {\
 *		if (lt == data[i].thread_id) { \
 *			return sizeof(pid_t) + data[i].data; \
 *		} \
 *	} \
 *	\
 *	tmp = realloc(data.data, (data.count + 1) * data.size); \

 *	if (nullptr == tmp) {
 *		assert("Failed to allocated thread local data");
 *	}

 *	data.data = data;
 *	*((pid_t*)&data.data[data.count]) = lt;
 *	++data.count;
 *	return sizeof(pid_t) + data.data;
 *}
 */

/* 
 * tcc does not implement <stdbool.h> or _Bool reliably 
 */
#if (WH_SYSTEM&WH_SYS_TCC)
    #ifndef __cplusplus
        #define true 1
        #define false 0
    #endif
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202311L)
    #define wh_no_return [[noreturn]]
    #define WH_DEPRECATED(_msg_) [[deprecated(_msg_)]]
#else
    #define wh_no_return _Noreturn
    #define WH_DEPRECATED(_msg_)
#endif

#endif /* _wh_header_common_c23_comp_ */

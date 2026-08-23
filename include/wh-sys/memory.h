#ifndef _wh_memory_
#define _wh_memory_

#include<wh-core/common.h>
#include<wh-types/memory.h>
#include<wh-params/memory.h>

WH_C()

extern i64 _wh_mem_scan(void);

// Heap functions
extern wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params);
extern void _wh_memory_tracking(_wh_memory_tracking_params params);

extern wh_heap_header_s* wh_heap_get(const char* name);
extern void wh_heap_print_table();

// Dedicated memory functions
extern void* (*_wh_alloc)(_wh_mem_alloc_params params);
extern void* (*_wh_realloc)(_wh_mem_realloc_params params);

extern void  (*_wh_free)(_wh_mem_free_params params);
extern void* (*_wh_disown)(_wh_mem_free_params params);
extern void* (*_wh_own)(_wh_own_params params);

extern void* _wh_calloc(_wh_calloc_params params);

// General functions
extern void _wh_heap_print(_wh_heap_print_params params);

// extern void* _wh_mem(_wh_mem_params params);
extern i32 wh_mem_leak_count(void);

#ifndef __cplusplu

/* [MD_DOC]
 *
 * ## wh_heap_init
 *
 * ```c
 * wh_heap_header_s* wh_heap_init(u64 bytes, u64* error: optional)
 * ```
 *
 * wh_heap_init is designed create new heaps from either the
 * global heap or from a sub-heap.
 *
 * | Name         | Type               | Status        | Comment                                                 |
 * | ------------ | ------------------ | ------------- | ------------------------------------------------------- |
 * | bytes        | uint64_t           | Implemented   | The number of bytes that will be allocated to the heap. |
 * | heap         | wh_heap_header_s*  | Implemented   | The heap from where the new heap will be created.       |
 * | error        | uint64_t           | Implemented   | Upon a error this variable is set if not nullptr.       |
 *
 * ### Return Value
 * Upon success a heap pointer is returned and on error a nullptr is returned.
 * 
 * ### See also
 * [common.h](include/wh-core/common.h)
 */
#define wh_heap_init(...)	WH_EPF(_wh_heap_init((_wh_heap_init_params) { __VA_ARGS__ }))

/* [MD_DOC
 *
 */
#define wh_memory_tracking(...) WH_EPF(_wh_memory_tracking((_wh_memory_tracking_params) { __VA_ARGS__ }))

/* [MD_DOC]
 *
 * @d_param(wh_heap_s*)		heap : The heap that will be printed.
 */
#define wh_heap_print(...) WH_EPF(_wh_heap_print((_wh_heap_print_params) { __VA_ARGS__ }))

/* [MD_DOC]
 *
 * ## wh_mem_free(void* owner, void* ptr, wh_heap_header_s* heap : optional, u64* error : optional)
 */
#define wh_free(...)    WH_EPF(_wh_free((_wh_mem_free_params) { __VA_ARGS__ }))
#define wh_disown(...)  WH_EPF(_wh_disown((_wh_mem_free_params) { __VA_ARGS__ }))
#define wh_own(...)     WH_EPF(_wh_own((_wh_own_params) { __VA_ARGS__ , .line = __LINE__, .file = __FILENAME__ }))
#define wh_inherit(ptr, old, new) wh_own(wh_disown(old), new)


/* [MD_DOC]
 *
 * ## wh_mem_alloc()
 */
#define wh_alloc(...) WH_EPF(_wh_alloc((_wh_mem_alloc_params) { __VA_ARGS__, .line = __LINE__, .file = __FILENAME__ }))

#define wh_calloc(...) WH_EPF(_wh_calloc((_wh_calloc_params) { __VA_ARGS__, .line = __LINE__, .file = __FILENAME__ }))

/* [MD_DOC]
 */
#define wh_realloc(...) WH_EPF(_wh_realloc((_wh_mem_realloc_params) { __VA_ARGS__ }))

/* [MD_DOC]
 */
//#define wh_mem(...) WH_EPF(_wh_mem((_wh_mem_params){ __VA_ARGS__ }))

#endif /* __cplusplus */

WH_C_END()
#endif /* _wh_memory_ */

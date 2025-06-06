#ifndef _wh_memory_
#define _wh_memory_

#include<wh/common.h>
#include<wh/sys/memory.h>
#include<wh/types/memory.h>
#include<wh/params/memory.h>

WH_C()

// Heap functions
extern void _wh_mem_free(_wh_mem_free_params params);
extern wh_heap_header_s* _wh_heap_init(_wh_heap_init_params params);

extern wh_heap_header_s* wh_heap_get(const char* name);
extern void wh_heap_print_table();

// Dedicated memory functions
extern void* _wh_mem_alloc(_wh_mem_alloc_params params);
extern void* _wh_mem_realloc(_wh_mem_realloc_params params);

// General functions
extern void _wh_heap_print(_wh_heap_print_params params);

extern void* _wh_mem(_wh_mem_params params);
extern i32 wh_mem_leak_count(void);

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
 * | Name  | Type               | Status        | Comment                                                 |
 * | ----- | ------------------ | ------------- | ------------------------------------------------------- |
 * | bytes | uint64_t           | Implemented   | The number of bytes that will be allocated to the heap. |
 * | heap  | wh_heap_header_s*  | Unimplemented | The heap from where the new heap will be created.       |
 * | error | uint64_t           | Implemented   | Upon a error this variable is set if not nullptr.       |
 *
 * ### Return Value
 * Upon success a heap pointer is returned and on error a nullptr is returned.
 * 
 * ### See also
 * [common.h](include/wh/common.h)
 */
#define wh_heap_init(...)	_wh_heap_init((_wh_heap_init_params) { __VA_ARGS__ })

/* [MD_DOC]
 *
 * @d_param(wh_heap_s*)		heap : The heap that will be printed.
 */
#define wh_heap_print(...) _wh_heap_print((_wh_heap_print_params) { __VA_ARGS__ })

/* [MD_DOC]
 *
 * ## wh_mem_free(void* owner, void* ptr, wh_heap_header_s* heap : optional, u64* error : optional)
 */
#define wh_mem_free(...)	_wh_mem_free((_wh_mem_free_params) { __VA_ARGS__ })


/* [MD_DOC]
 *
 * ## wh_mem_alloc()
 */
#define wh_mem_alloc(...)	_wh_mem_alloc((_wh_mem_alloc_params) { __VA_ARGS__ })

/* [MD_DOC]
 */
#define wh_mem_realloc(...) _wh_mem_realloc((_wh_mem_realloc_params) { __VA_ARGS__ })

/* [MD_DOC]
 */
#define wh_mem(...)			_wh_mem((_wh_mem_params){ __VA_ARGS__ })

WH_C_END()
#endif /* _wh_memory_ */

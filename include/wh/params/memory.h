#ifndef _wh_header_params_memory_
#define _wh_header_params_memory_

#include<wh/common.h>
#include<wh/types/memory.h>

typedef struct {
	u64 bytes;
	wh_heap_header_s* heap;
	u64 type;
	u64* error;
} _wh_heap_init_params;

typedef struct {
	wh_heap_header_s* heap;
	u64 bytes;
	void* owner;
	u64 flags;
	u64* error;
} _wh_mem_alloc_params;

typedef struct {
	wh_heap_header_s* heap;
	void* ptr;
	u64 bytes;
	u64 flags;
	u64* error;
} _wh_mem_realloc_params;

typedef struct {
	wh_heap_header_s* heap;
	void* ptr;
	void* owner;
	u64* error;
} _wh_mem_free_params;

typedef struct {
	size_t bytes;
	void* ptr;
	uint32_t flags;
} _wh_mem_params;


#endif /* _wh_header_params_memory_ */

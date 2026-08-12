#ifndef _wh_header_memory_arena_
#define _wh_header_memory_arena_

#include <wh-types/memory.h>
#include <wh-params/memory.h>

void* _wh_mem_alloc_arena(_wh_mem_alloc_params* params);
void _wh_mem_free_arena(_wh_mem_free_params* params);

#endif /* _wh_header_memory_arena_ */

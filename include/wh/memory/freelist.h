#ifndef _wh_header_memory_freelist_
#define _wh_header_memory_freelist_

#include<wh-types/memory.h>
#include<wh-params/memory.h>

extern void* _wh_mem_alloc_freelist(_wh_mem_alloc_params* params);
extern wh_heap_node_s* _wh_mem_freelist_previous(_wh_mem_free_params* params, wh_heap_node_s* pn, wh_heap_node_s* cn);
extern void _wh_mem_freelist_next(_wh_mem_free_params* params, wh_heap_node_s* nn, wh_heap_node_s* cn);
extern void _wh_mem_free_freelist(_wh_mem_free_params* params);
extern void* _wh_mem_realloc_freelist(_wh_mem_realloc_params* params);

#endif /* _wh_header_memory_freelist_ */

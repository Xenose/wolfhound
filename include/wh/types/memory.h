#ifndef _wh_header_types_memory_
#define _wh_header_types_memory_

#include<wh/common.h>

#define WH_MEM_ZERO		((u64)0x0001)
#define WH_MEM_IN_USE	((u64)0x0002)
#define WH_MEM_IS_HEAP	((u64)0x0004)

typedef struct _wh_heap_node_s {
	struct_type stype;

	// non atomic data
	u64 bytes;
	u64 flags;

	struct _wh_heap_node_s* next;
	struct _wh_heap_node_s* previous;

	// start of the data
	void* data;
} wh_heap_node_s;

typedef struct {
	wh_heap_node_s* nodes;
} _wh_heap_header_freelist_s;

typedef struct {
	void* start;
} _wh_heap_header_arena_s;

typedef struct _wh_heap_header_s {
	struct_type stype;
	aflag locked;

	i64 allocation_count;
	u64 bytes_used;
	u64 bytes_free;

	union {
		_wh_heap_header_freelist_s freelist;
		_wh_heap_header_arena_s arena;
	};
} wh_heap_header_s;


#endif /* _wh_header_types_memory_ */

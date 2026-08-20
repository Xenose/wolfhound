#ifndef _wh_header_sys_memory_tracker_
#define _wh_header_sys_memory_tracker_

#include<wh-core/common.h>
#include<wh-sys/memory.h>

typedef struct {
    void** ptr;
    u64 line;
    const char* file;
} _wh_owner_s;

typedef struct {
    void* ptr;
    wh_heap_header_s* heap;
    _wh_owner_s* owners;
    u64 owner_count;
} _wh_heap_ptr_pair_s;

extern void _wh_tracker_remove(void* owner, void* ptr);
extern void _wh_tracker_add(void* owner, void* ptr, _wh_heap_ptr_pair_s* entry, u64 line, const char* file);
extern void _wh_tracker_insert(void* owner, void* ptr, wh_heap_header_s* heap, u64 line, const char* file);


#endif /* _wh_header_sys_memory_tracker_ */

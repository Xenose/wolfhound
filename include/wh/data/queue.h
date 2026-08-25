#ifndef _wh_header_data_queue_
#define _wh_header_data_queue_

#include<wh-core/common.h>

typedef struct _wh_queue_node_s{
    struct_type stype;

    // The next node
    struct _wh_queue_node_s* previous;
    struct _wh_queue_node_s* next_used;
    struct _wh_queue_node_s* next_free;

    // User data
    void* data;
} wh_queue_node_s;

typedef struct _wh_queue_s {
    struct_type stype;

    // Metadata
    u64 size;
    u64 type_size;

    // If memory allocation was done we need a destructor.
    void (*destructor)(struct _wh_queue_s* queue);

    // Queue pointer
    wh_queue_node_s* queue;

    wh_queue_node_s* head;
    wh_queue_node_s* tail;
} wh_queue_s;

#endif /* _wh_header_data_queue_ */

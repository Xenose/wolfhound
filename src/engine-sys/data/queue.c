#include<wh-sys/data/queue.h>

// Draft of the queue system

typedef struct {
    void* (*init)(wh_queue_s* queue);
    void* (*insert)(wh_queue_s* queue, void* data);
    void* (*read)(wh_queue_s* queue);
    void* (*pop)(wh_queue_s* queue);
    void (*resize)(wh_queue_s* queue, i64 count);
    void (*delete)(wh_queue_s* queue);
    void (*for_each)(wh_queue_s* queue, void (*pe)(void* data));
    void (*pop_each)(wh_queue_s* queue, void (*pe)(void* data));
} _queue;

static _queue _funcs[] = {
    // wolfhound
    {
    },
    // system memory
    {
    },
    // std malloc
    {
    },
};

static void* _init(wh_queue_s* queue) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    return _funcs[index].init(queue);
}


static void* _insert(wh_queue_s* queue, void* data) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    return _funcs[index].insert(queue, data);
}

// reads data without removing it.
static void* _read(wh_queue_s* queue) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    return _funcs[index].read(queue);
}
// reads and remove item.
static void* _pop(wh_queue_s* queue) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    return _funcs[index].pop(queue);
}

static void _resize(wh_queue_s* queue, i64 count) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    _funcs[index].resize(queue, count);
}

static void _delete(wh_queue_s* queue) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    _funcs[index].delete(queue);
}

static void _for_each(wh_queue_s* queue, void (*pe)(void* data)) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    _funcs[index].for_each(queue, pe);
}

static void _pop_each(wh_queue_s* queue, void (*pe)(void* data)) {
    i64 index = queue->stype - WH_STRUCT_TYPE_QUEUE_WOLF;
    _funcs[index].pop_each(queue, pe);
}

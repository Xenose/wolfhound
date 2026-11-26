#ifndef _wh_header_types_foreman_
#define _wh_header_types_foreman_

#include<wh-core/common.h>
#include<wh-sys/atomic_lock.h>
#include<wh-types/gameinfo.h>
#include<wh-types/stack.h>
#include<wh-sys/data/dynamic_array.h>

enum {
    WH_WORKER_RUN = 0,
    WH_WORKER_PAUSE,
    WH_WORKER_HALT,
};

typedef struct {
    struct_type stype;
    wh_atomic_lock_s lock;
    wh_action_s* ptr;
} wh_task_s;

typedef struct {
    struct_type stype;
    i64 state;
    pid_t tid;
    wh_raw_stack_s stack;
    wh_atomic_lock_s lock;

    struct {
        u64 count;
        wh_task_s ptr;
    } tasks;
} wh_worker_s;

typedef struct {
    struct_type stype;

    wh_darray_s workers;    // threads/workers
    wh_darray_s queue;      // tasks for the workers
} wh_foreman_s;

#endif /* _wh_header_types_foreman_ */

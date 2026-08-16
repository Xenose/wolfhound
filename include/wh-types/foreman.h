#ifndef _wh_header_types_foreman_
#define _wh_header_types_foreman_

#include<wh-core/common.h>
#include<wh-sys/atomic_lock.h>
#include<wh-types/gameinfo.h>
#include<wh/data/dynamic_array.h>

typedef struct {
    struct_type stype;
    wh_atomic_lock_s lock;
    wh_action_s* ptr;
} wh_task_s;

typedef struct {
    struct_type stype;

    struct {
        u64 count;
        wh_task_s ptr;
    } tasks;
} wh_worker_s;

typedef struct {
    struct_type stype;
    wh_darray_s workers;
    wh_darray_s actions;
} wh_foreman_s;

#endif /* _wh_header_types_foreman_ */

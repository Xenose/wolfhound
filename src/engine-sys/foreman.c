#include<wh-posix/unistd.h>
#include<wh-sys/foreman.h>
#include<wh/debug/logger.h>


void wh_worker() {
}

void wh_foreman_init(wh_instance_s* ins, wh_foreman_s* foreman) {
    _wh_darray_init_params d_params = {
        .stype = WH_STRUCT_TYPE_DYNAMIC_ARRAY_STD,
        .array = &foreman->workers,
        .type_size = sizeof(wh_worker_s),
    };

    if (0 == ins->config.foreman.worker.count) {
        d_params.count = 4;
    } else {
        d_params.count = ins->config.foreman.worker.count;
    }

    _wh_darray_init(d_params);
    wh_log_debug(("Foreman reporting for duty! Worker count [ %i ]"), d_params.count);
}

void worker_loop(u64 index, void* data) {
    wh_log_debug(("Sending work to worker [ %i ]"), index);
}

// Idea foreman assigns work to the worker queue,
// and the pointer back tells the foreman when the
// worker was done with the work.
void wh_foreman_execute(wh_foreman_s* foreman) {
    wh_darray_for_each(&foreman->workers, worker_loop);
    usleep(100000);
}

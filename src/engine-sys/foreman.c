#include<wh-sys/foreman.h>
#include<wh/debug/logger.h>


void _wh_foreman_init(wh_foreman_s* foreman) {
    wh_log_debug(("Foreman reporting for duty!"));
}

// Idea foreman assigns work to the worker queue,
// and the pointer back tells the foreman when the
// worker was done with the work.
void _wh_foreman_execute(wh_foreman_s* foreman) {
    u64 worker_count = foreman->workers.count;
    wh_worker_s* workers = foreman->workers.ptr;

    for (u64 i = 0; i < worker_count; i++) {
        wh_log_debug(("Sending work to worker [ %i ]"), i);
    }
}

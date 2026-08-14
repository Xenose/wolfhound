#include<wh-posix/unistd.h>
#include<wh-sys/foreman.h>
#include<wh/debug/logger.h>


void wh_worker() {
}

void wh_foreman_init(wh_instance_s* ins, wh_foreman_s* foreman) {
    if (0 == ins->config.foreman.worker.count) {
        foreman->workers.count = 4;
    } else {
        foreman->workers.count = ins->config.foreman.worker.count;
    }

    wh_log_debug(("Foreman reporting for duty! Worker count [ %i ]"), ins->config.foreman.worker.count);
}

// Idea foreman assigns work to the worker queue,
// and the pointer back tells the foreman when the
// worker was done with the work.
void wh_foreman_execute(wh_foreman_s* foreman) {
    u64 worker_count = foreman->workers.count;
    wh_worker_s* workers = foreman->workers.ptr;

    for (u64 i = 0; i < worker_count; i++) {
        wh_log_debug(("Sending work to worker [ %i ]"), i);
    }

    sleep(1);
}

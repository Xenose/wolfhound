#include<wh-posix/sched.h>
#include<wh-sys/foreman.h>
#include<wh-sys/debug/logger.h>

#include<wh-sys/atomic_lock.h>
#include<wh-posix/unistd.h>

// The actual worker loop
int wh_worker(void* ptr) {
    wh_worker_s* worker = ptr;

    do {
        wh_debug(("[ %i ] Worker saying hello!"), gettid());
        usleep(150000);
    } while(WH_WORKER_HALT != atomic_load(&worker->state));

    return 0;
}

static void _worker_create(u64, void* ptr) {
    wh_worker_s* worker = ptr;
    int flags = CLONE_SIGHAND | CLONE_VM;

    worker->stack.size = 1024 * 1024;
    worker->stack.ptr = wh_alloc(nullptr, worker->stack.size, &worker->stack.ptr);

    if (nullptr == worker->stack.ptr) {
        wh_emergency(("Failed to allocate memory"));
    }

    worker->tid = clone(&wh_worker, &worker->stack.bytes[worker->stack.size], flags, worker);
}

static void _worker_destroy(u64, void* ptr) {
    wh_worker_s* worker = ptr;
    atomic_store(&worker->state, WH_WORKER_HALT);
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
    wh_darray_for_each(&foreman->workers, _worker_create);
}

void wh_foreman_destroy(wh_instance_s*, wh_foreman_s* foreman) {
    wh_darray_for_each(&foreman->workers, _worker_destroy);
    sleep(1);
}

void worker_loop(u64 index, void* data) {
    wh_log_debug(("Sending work to worker [ %i ]"), index);
}

// Idea foreman assigns work to the worker queue,
// and the pointer back tells the foreman when the
// worker was done with the work.
void wh_foreman_execute(wh_foreman_s* foreman) {
    wh_darray_for_each(&foreman->workers, worker_loop);
    usleep(150000);
}

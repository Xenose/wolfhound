#include <wh-sys/debug/logger.h>
#include <wh-sys/memreq.h>
#include <wh-posix/unistd.h>
#include <wh-posix/string.h>

#include <wh-posix/errno.h>
#include <wh-posix/sys/mman.h>

void* _wh_sys_memreq(_wh_sys_memreq_params params) {
    size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
    void* mem = mmap(
            nullptr, params.bytes, PROT_READ | PROT_WRITE, 
            MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (MAP_FAILED == mem) {
        wh_log_critical(("Failed to allocated heap! [ $n ]"), errno);
        goto go_error_exit;
    }

    for(size_t i = 0; i < params.bytes; i += page_size) {
        u8* ptr = wh_ptr_add(mem, i);
        *ptr = 0;
    }

    return mem;
go_error_exit:
    return nullptr;
}

void _wh_sys_memrel(_wh_sys_memrel_params params) {
    if (-1 == munmap(params.ptr, params.len)) {
        wh_log_critical(("$n value [ ptr : %lu, len : %lu"), 
                errno, params.ptr, params.len);
    }
}

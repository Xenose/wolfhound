#include<wh/debug/logger.h>
#include<wh/sys/memory.h>
#include<string.h>

#ifdef __unix__
#include<errno.h>
#include<sys/mman.h>

void* _wh_sys_memreq(_wh_sys_memreq_params params) {
	void* mem = mmap(
		nullptr, params.bytes, PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (MAP_FAILED == mem) {
		wh_log_critical(("Failed to allocated heap! [ $n ]"), errno);
		goto go_error_exit;
	}

	for(size_t i = 0; i < params.bytes; i += 4096) {
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



#elif defined(_WIN64)
#include<windows.h>
	
void* _wh_sys_memreq(_wh_sys_memreq_params params) {
	void* mem = nullptr;

	mem = VirtualAlloc(nullptr, params.bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (nullptr == mem) {
		wh_log_error(("Failed to allocate memory!"));
		goto go_error_exit;
	}

	wh_log_debug(("Allocated [ %d ] bytes."), params.bytes);
	return mem;
go_error_exit:
	return nullptr;
}

void _wh_sys_memrel(_wh_sys_memrel_params params) {
	if (0 == VirtualFree(params.ptr, 0, MEM_RELEASE)) {
		wh_log_critical(("EINVAL value [ ptr : %lu, len : %lu"), 
						params.ptr, params.len);
	}
}

#endif /* system dependent code */

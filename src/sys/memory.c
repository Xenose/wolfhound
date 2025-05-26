#include<wh/debug.h>
#include<wh/sys/memory.h>

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

		wh_log_debug(("At bytes [ %d ] of [ %d ]"), i, params.bytes);
		*ptr = 0;
	}

	return mem;
go_error_exit:
	return nullptr;
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

#endif /* system dependent code */



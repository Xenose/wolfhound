#include <wh-posix/windows.h>

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

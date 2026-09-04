#include <wh/string.h>
#include <wh-sys/debug/logger.h>
#include <wh-sys/dynamic_object.h>

#ifdef __unix__
#include <wh-posix/dlfcn.h>

wh_dynamic_s wh_sys_dynamic_open(const char* path) {
	char file_path[256] = { 0 };
	wh_dynamic_s dlo = { 0 };

	wh_strcat((file_path, 255), file_path, ".so");
	dlo.handle = dlopen(file_path, RTLD_NOW);

	if (nullptr == dlo.handle) {
		wh_log_error(("Failed to load dynamic object [ %s ]"), file_path);
		goto go_error_exit;
	}

go_error_exit:
	return dlo;
}

void* wh_sys_dynamic_load(const wh_dynamic_s* restrict lib, const char* restrict func_name) {
	void* out = nullptr;

	if (nullptr == lib || nullptr == func_name) {
		goto go_error_exit;
	}

	out = dlsym(lib->handle, func_name);

go_error_exit:
	return out;
}

void wh_sys_dynamic_close(wh_dynamic_s* lib) {
	dlclose(lib->handle);
}

#endif


#include "wh/types/library.h"
#include<wh/debug/logger.h>
#include<wh/sys/library.h>

#ifdef __linux__
#include<string.h>
#include<dirent.h>
#include<dlfcn.h>
#include<stdlib.h>

wh_lib_s _wh_libopen(_wh_libopen_params params) {
	char* error = nullptr;
	wh_lib_s lib = { 0 };

	dlerror();
	lib._linux = dlopen(params.filename, RTLD_NOW | RTLD_GLOBAL);
	error = dlerror();

	if (nullptr != error) {
		wh_log_error(("Failed to load [ %s ]"), params.filename, error);
	}

	return lib;
}

void* _wh_libget(_wh_libget_params params) {
	char* error = nullptr;

	dlerror();
	*params.func = dlsym(params.lib->_linux, params.name);
	error = dlerror();

	if (nullptr != error) {
		wh_log_error(("Failed to load [ %s ] error [ %s ]"), params.name, error);
		return nullptr;
	}

	wh_log_info(("loaded function [ %s ]"), params.name);
	return *params.func;
}

void _wh_libclose(wh_lib_s* lib) {
	if (lib && lib->_linux) {
		dlclose(lib->_linux);
		lib->_linux = NULL;
	}
}

i8 _wh_libfind(const char* name, char** paths, u64 length) {
	DIR* dir = nullptr;
	struct dirent* dp;

	wh_for(u64, i, length) {
		dir = opendir(paths[i]);

		while (nullptr != (dp = readdir(dir))) {
			if (!strcmp(name, dp->d_name)) {
				wh_print(("Directory [ %s ]\n"), dp->d_name);
			}
		}

		closedir(dir);
	}

	return 0;
}

#elif _WIN64
#include<windows.h>
#include<libloaderapi.h>
#include<wingdi.h>

wh_lib_s _wh_libopen(_wh_libopen_params params) {
	wh_lib_s out = { 0 };

	out._windows = LoadLibrary(params.filename);

	if (nullptr == out._windows) {
		wh_log_error(("Failed to load DLL [ %s ]"), params.filename);
	}

	return out;
}

void* _wh_libget(_wh_libget_params params) {
	if (nullptr == params.lib->_windows) {
		goto go_error_exit;
	}

	*params.func = (void*)GetProcAddress(params.lib->_windows, params.name);

go_error_exit:
	return *params.func;
}

void _wh_libclose(wh_lib_s* lib) {
	 FreeLibrary(lib->_windows);
}

i8 _wh_libfind(const char* name, char** paths, u64 length) {
	return 0;
}

#endif

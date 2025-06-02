#include "wh/file.h"
#include<fcntl.h>
#include<wh/file.h>
#include<wh/debug.h>

#include<errno.h>

#ifdef __linux__
#include<unistd.h>
#include<sys/mman.h>

wh_file_s _wh_file_load(_wh_file_load_params params) {
	int fd = open(params.path, 0, 0);
	wh_file_s file = { 0 };

	if (-1 == fd) {
		wh_log_error(("Failed to find file [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.length = lseek(fd, 0, SEEK_END);

	if (0 >= file.length) {
		wh_log_error(("Failed to get length [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.ptr = mmap(nullptr, file.length, PROT_READ, MAP_SHARED, fd, 0);

	if (MAP_FAILED == file.ptr) {
		wh_log_error(("Failed to mmap file"));
		goto go_error_exit;
	}

	return file;
go_error_exit:
	return (wh_file_s){ 0 };
}

i8 _wh_file_unload(_wh_file_unload_params params) {
	if (-1 == munmap(params.file.ptr, params.file.length)) {
		wh_log_error(("munmap failed [ $n ]"), errno);
	}

	return 0;
go_error_exit:
	return -1;
}

#else
#include<windows.h>

wh_file_s _wh_file_load(_wh_file_load_params params) {
	wh_file_s file = { 0 };

	HANDLE fd = CreateFile(
		params.path, READ_CONTROL, 0, nullptr,
		OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);

	file.length = GetFileSize(fd, nullptr);

	file.ptr = CreateFileMappingA(fd, nullptr, PAGE_READONLY, 0, 0, nullptr);
	return file;
}

i8 _wh_file_unload(_wh_file_unload_params params) {
	return 0;
}

#endif

#include<wh-posix/windows.h>

wh_file_s _wh_file_load(_wh_file_load_params params) {
	wh_file_s file = { 0 };
	_wh_file_windows_s* windows = &file._windows;

	windows->h_fd = CreateFileA(
		params.path, GENERIC_READ, FILE_SHARE_READ, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == windows->h_fd) {
		wh_log_error(("Failed to open file [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.length = GetFileSizeEx(windows->h_fd, nullptr);

	if (INVALID_FILE_SIZE == file.length) {
		wh_log_error(("Failed to get file size [ %s ]"), params.path);
		goto go_error_exit_close_fd;
	}

	windows->h_map = CreateFileMappingA(windows->h_fd, nullptr, PAGE_READONLY, 0, 0, nullptr);

	if (nullptr == windows->h_map) {
		wh_log_error(("Failed to create file mapping [ %s ]"), params.path);
		goto go_error_exit_close_fd;
	}

	file.ptr = MapViewOfFile(windows->h_map, FILE_MAP_READ, 0, 0, 0);

	if (nullptr == file.ptr) {
		wh_log_error(("Failed to map view of file [ %s ]"), params.path);
		goto go_error_exit_close_mapping;
	}

	return file;
go_error_exit_close_mapping:
	CloseHandle(windows->h_map);
go_error_exit_close_fd:
	CloseHandle(windows->h_fd);
go_error_exit:
	return (wh_file_s) { 0 };
}

i8 _wh_file_unload(_wh_file_unload_params params) {
	_wh_file_windows_s* windows = &params.file._windows;

	if (nullptr != params.file.ptr) {
		UnmapViewOfFile(params.file.ptr);
	}

	if (nullptr != windows->h_map) {
		CloseHandle(windows->h_map);
	}

	if (INVALID_HANDLE_VALUE != windows->h_fd && nullptr != windows->h_fd)  {
		CloseHandle(windows->h_fd);
	}

	return 0;
}

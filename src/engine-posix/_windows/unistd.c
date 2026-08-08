#include<wh-posix/unistd.h>
#include<wh-posix/time.h>

#include<wh-posix/_windows/fd_table.h>
#include<wh-posix/_windows/wnt.h>

#include<windows.h>

int getpagesize(void) {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return (int)si.dwPageSize;
}

//int nanosleep() {
//	NtDelayExecution(TRUE, 100);
//}

int usleep(useconds_t usec) {
    // 1. Setup timer
    HANDLE h_timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (!h_timer) return -1;

    LARGE_INTEGER li_due_time;
    // Set wait time (negative for relative)
    li_due_time.QuadPart = -10 * (long long)usec;

    // 2. Set timer
    if (!SetWaitableTimer(h_timer, &li_due_time, 0, NULL, NULL, FALSE)) {
        CloseHandle(h_timer);
        return -1;
    }

    // 3. Block until signal
    // Using simple WaitForSingleObject to ensure we don't return on APCs
    DWORD wait_result = WaitForSingleObject(h_timer, INFINITE);
    
    CloseHandle(h_timer);
    
    // POSIX usleep returns 0 on success, -1 on failure
    return (wait_result == WAIT_OBJECT_0) ? 0 : -1;
}

int sleep(unsigned int seconds) {
	struct timespec start = { 0 };
	struct timespec end = { 0 };

	clock_gettime(CLOCK_MONOTONIC, &start);
	
	if (WAIT_IO_COMPLETION == SleepEx(seconds * 1000, true)) {
		return 0;
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	return (seconds - (end.tv_sec - start.tv_sec));
}

int access(const char* path, int amode) {
	int length = strnlen(path, MAX_PATH + 1);
	WIN32_FILE_ATTRIBUTE_DATA attrib = { 0 };

	if (MAX_PATH < length) {
		errno = ENAMETOOLONG;
		goto go_error;
	}

	if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attrib)) {
		DWORD error = GetLastError();

		switch (error) {
			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				errno = ENOENT;
				break;

			case ERROR_ACCESS_DENIED:
				errno = EACCES;
				break;

			case ERROR_INVALID_NAME:
				errno = ENOENT;
				break;

			default:
				errno = EIO;
				break;
		}

		goto go_error;
	}

	if (F_OK == amode) {

	} else {
		if (W_OK & amode) {
			/*if (FILE_ATTRIBUTE_READONLY & attrib.dwFileAttributes) {
				errno = EROFS;
				goto go_error;
			}*/
		}
	}

	return 0;
go_error:
	return -1;
}
	
int dup(int oldfd) {
	int fd = -1;
	_wnt_fd_entry entry = { 0 };

	if (-1 == _wnt_table(oldfd, _WNT_FDOP_GET, &entry)) {
		errno = EBADF;
		goto go_error_exit;
	}

	switch (entry.type) {
		case _WNT_FD_TYPE_HANDLE: {
			HANDLE tmp = entry.data.handle;
			entry = (_wnt_fd_entry){ 0 };

			// DuplicateHandle()
		}
	}

go_error_exit:
	return fd;
}

ssize_t write(int fd, const void* buffer, size_t count) {
	ssize_t bytes = -1;
	_wnt_entry_s entry = { 0 };

	if (-1 == _wnt_call(_WNT_CALL_FD_GET, fd, &entry)) {
		errno = EBADF;
		goto go_error_exit;
	}

	switch (entry.type) {
		case _WNT_ENTRY_HANDLE:
		case _WNT_ENTRY_STD: {
				DWORD b = 0;

				if (!WriteFile(entry.handle, buffer, (DWORD)count, &b, nullptr)) {
					DWORD err = GetLastError();

					switch (err) {
						case ERROR_INVALID_HANDLE: errno = EBADF;		break;
						case ERROR_ACCESS_DENIED:	errno = EACCES; 	break;
						case ERROR_DISK_FULL:		errno = ENOSPC; 	break;
						default:							errno = EIO;		break;
					}

					goto go_error_exit;
				}

				bytes = (ssize_t)b;
			}
			break;
		default:
			errno = ENOTSUP;
	}

go_error_exit:
	return bytes;
}

pid_t gettid(void) {
	return (pid_t)GetCurrentThreadId();
}
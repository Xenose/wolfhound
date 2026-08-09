#include<wh-posix/unistd.h>
#include<wh-posix/time.h>

#include<wh-posix/_windows/wnt.h>

#include<wh-posix/windows.h>

int close(int fd) {
	_wnt_entry_s entry = { 0 };

	// Posix allows freeing 0,1,2 but this would break
	// our windows version, so instead just ignore it
	// and report 0 == success.
	switch (fd) {
		case 0:
		case 1:
		case 2:
			goto go_skip;
	}

	if (0 != _wnt_call(_WNT_CALL_FD_GET, fd, &entry)) {
		goto go_error_exit;
	}

	switch(entry.type) {
		case _WNT_ENTRY_HANDLE:
			CloseHandle(entry.handle);
			break;
		case _WNT_ENTRY_SOCKET:
			if (SOCKET_ERROR == closesocket(entry.sock)) {
				// TODO errno
			}
			break;
		default:
			// TODO add errno
			{}
	}

	if (0 != _wnt_call(_WNT_CALL_FD_DELETE, fd)) {
		// TODO errno
	}

go_skip:
	return 0;
go_error_exit:
	return -1;
}

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
		_wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_NORMAL, error, &errno);
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
	_wnt_entry_s entry = { 0 };

	if (-1 == _wnt_call(_WNT_CALL_FD_GET, oldfd, &entry)) {
		errno = EBADF;
		goto go_error_exit;
	}

	switch (entry.type) {
		case _WNT_ENTRY_HANDLE: {
			HANDLE tmp = entry.handle;
			// DuplicateHandle()
		}
	}

go_error_exit:
	return fd;
}

long sysconf(int name) {
	switch(name) {
		case _SC_PAGESIZE:
			return (long)getpagesize();
		default:
			errno = EINVAL;
			return -1;
	}
}

off_t lseek(int fd, off_t offset, int whence) {
	off_t off = 0;
	_wnt_entry_s entry = { 0 };

	LARGE_INTEGER _offset = { 0 };
	LARGE_INTEGER _off = { 0 };

	if (-1 == _wnt_call(_WNT_CALL_FD_GET, fd, &entry)) {
		errno = EBADF;
		goto go_error_exit;
	}

	if (_WNT_ENTRY_HANDLE != entry.type) {
		errno = ESPIPE;
		goto go_error_exit;
	}

	_offset.QuadPart = offset;

	switch(whence) {
		case SEEK_SET:
			_off.QuadPart = offset;
			break;

		case SEEK_CUR:
			if (0 == SetFilePointerEx(entry.handle, _offset, &_off, FILE_CURRENT)) {
				_wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_NORMAL, GetLastError(), &errno);
				goto go_error_exit;
			}
			break;

		case SEEK_END:
			if (0 == SetFilePointerEx(entry.handle, _offset, &_off, FILE_END)) {
				_wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_NORMAL, GetLastError(), &errno);
				goto go_error_exit;
			}
			break;

		default:
			errno = EINVAL;
			goto go_error_exit;
	}

	if (0 > _off.QuadPart) {
		errno = EINVAL;
		goto go_error_exit;
	}

	if (!SetFilePointerEx(entry.handle, _off, nullptr, FILE_BEGIN)) {
		errno = EINVAL;
		goto go_error_exit;
	}

	off = _off.QuadPart;
	return off;
go_error_exit:
	return -1;
}

pid_t gettid(void) {
	return (pid_t)GetCurrentThreadId();
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
					DWORD error = GetLastError();
					_wnt_call(_WNT_CALL_ERROR_2_ERRNO, _WNT_ERROR_TYPE_NORMAL, error, &errno);
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
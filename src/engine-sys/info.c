#include<wh-sys/info.h>
#include<wh-posix/unistd.h>
#include<wh-posix/string.h>

#include<wh/print.h>

static wh_thread i64 _thread_id = -1;

i64 wh_sys_gettid(void) {
	#if (WH_SYSTEM&WH_SYS_TCC)
		return (i64)gettid();
	#else
		return -1 == _thread_id ? (_thread_id = (i64)gettid()) : _thread_id;
	#endif
}

#ifdef __linux__

/* [MD_DOC]
 * Gets the path to the current executable/binary
 */
i64 wh_sys_program_path(char* buffer, u64 buffer_size) {
	i64 length = readlink("/proc/self/exe", buffer, buffer_size);

	if (-1 == length) {
		return length;
	}

	--length;

	while (0 < length && '/' != buffer[length]) {
		buffer[length--] = '\0';
	}

	return length;
}

#elif defined(_WIN32)
#include<wh-posix/windows.h>

i64 wh_sys_program_path(char* buffer, u64 buffer_size) {
	DWORD length = GetModuleFileNameA(
		nullptr, buffer, (DWORD)buffer_size);

	if (0 == length) {
		return -1;
	}

	--length;

	while (0 < length && '\\' != buffer[length]) {
		buffer[length--] = '\0';
	}

	return length;
}

#endif

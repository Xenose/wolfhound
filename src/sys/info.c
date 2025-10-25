#include<wh/sys/info.h>
#include<wh/wrap/unistd.h>
#include<wh/wrap/string.h>

#include<wh/print.h>

u64 _wh_sys_pagesize(void) {
	return getpagesize();
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
#include<windows.h>

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

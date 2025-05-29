#include<wh/wrap/unistd.h>

#if defined(_WIN32)

int getpagesize(void) {
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
}

#endif /* win32 */

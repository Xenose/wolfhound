#include<wh-posix/time.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
	#include"_windows/time.c"
#endif

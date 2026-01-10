#include<wh-common/os.h>
#include<wh-posix/signal.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
	#include"_windows/signal.c"
#endif


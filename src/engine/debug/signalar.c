#include<wh/debug/signalar.h>

#ifdef WH_UNWIND_NOT_FOUND
	#include"_unwind/signalar.c"
#elif (WH_SYSTEM&WH_SYS_LINUX)
	#include"_linux/signalar.c"
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#include"_windows/signalar.c"
#else
	#include"_posix/signalar.c"
#endif

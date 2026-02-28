#include<wh-common/os.h>
#include<wh-posix/unistd.h>
#include<wh-maths/core.h>

#if (WH_SYSTEM&WH_SYS_LINUX)
	#include"_linux/unistd.c"
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#include"_windows/unistd.c"
#elif (WH_SYSTEM&(WH_SYS_BSD))
	#include"_bsd/unistd.c"
#elif (WH_SYSTEM&(WH_SYS_SOLARIS))
	#include"_solaris/unistd.c"
#elif (WH_SYSTEM&(WH_SYS_BEOS))
	#include"_beos/unistd.c"
#endif

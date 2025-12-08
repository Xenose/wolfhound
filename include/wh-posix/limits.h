#ifndef _wh_header_posix_limits_
#define _wh_header_posix_limits_

#include<wh-common/os.h>
#include<limits.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<unistd.h>

	#ifndef NAME_MAX
		#define NAME_MAX 256
	#endif
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#ifndef NAME_MAX
		// Don't ask me about magic numbers...
		#define NAME_MAX 255
	#endif
#endif

#endif

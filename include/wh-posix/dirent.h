#ifndef _wh_header_posix_dirent_
#define _wh_header_posix_dirent_

#include<wh-common/os.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<dirent.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	typedef struct dirent {
		ino_t	d_ino;
		char	d_name[];
	} DIR;
#endif

#endif

#ifndef _wh_header_posix_dirent_
#define _wh_header_posix_dirent_

#include<wh-common/os.h>

#include<wh-posix/limits.h>
#include<wh-posix/sys/types.h>

#if (WH_SYSTEM&WH_SYS_WINDOWS)
	typedef struct dirent {
		ino_t	d_ino;
		char	d_name[NAME_MAX + 1];
	};

	typedef struct {
		void* handle;
		struct dirent entry;
		int valid;
	} DIR;

	extern int alphasort(const struct dirent**, const struct dirent**);
	extern int closedir(DIR*);
	extern int dirfd(DIR*);
	extern DIR* fdopendir(int fd);
	extern DIR* opendir(const char* path);
	extern struct dirent* readdir(DIR*);
	extern int readdir_r(DIR*, struct dirent*);
	extern void rewinddir(DIR*);
	extern int scandir(
		const char*, struct dirent***,
		int(*)(const struct dirent*),
		int(*)(const struct dirent**),
		const struct dirent**
	);
	extern void seekdir(DIR*, long);
	extern long telldir(DIR*);

#endif

#endif
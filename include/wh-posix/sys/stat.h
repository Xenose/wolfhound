#ifndef _wh_header_posix_sys_stat_
#define _wh_header_posix_sys_stat_

#include<wh-common/os.h>
#include<wh-posix/sys/types.h>
#include<wh-posix/time.h>

#if (WH_SYSTEM&WH_SYS_POSIX)
	#include<sys/stat.h>
#elif (WH_SYSTEM&WH_SYS_WINDOWS)
	#define S_IFMT   0170000 // Bit mask for the file type bit field
	#define S_IFSOCK 0140000 // socket
	#define S_IFLNK  0120000 // symbolic link
	#define S_IFREG  0100000 // regular file
	#define S_IFBLK  0060000 // block device
	#define S_IFDIR  0040000 // directory
	#define S_IFCHR  0020000 // character device
	#define S_IFIFO  0010000 // FIFO

	#define S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
	#define S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)
	#define S_ISLNK(m)  (((m) & S_IFMT) == S_IFLNK)
	#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
	#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
	#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
	#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)

	struct stat {
		dev_t			st_dev;
		ino_t			st_ino;
		mode_t		st_mode;
		nlink_t		st_nlink;
		uid_t			st_uid;
		gid_t			st_gid;
		dev_t			st_rdev;
		off_t 		st_size;
		blksize_t	st_blksize;
		blkcnt_t 	st_blocks;

		/*
		 * Since POSIX.1-2008, this structure supports nanosecond
		 * precision for the following timestamp fields.
		 * For the details before POSIX.1-2008, see HISTORY.  
		 */

		struct timespec st_atim;
		struct timespec st_mtim;
		struct timespec st_ctim;

		#define st_atime st_atim.tv_sec
		#define st_mtime st_mtim.tv_sec
		#define st_ctime st_ctim.tv_sec
	};

	extern int stat(const char* path, struct stat* statbuf);
	extern int fstat(int fd, struct stat* statbuf);
	extern int lstat(const char* path, struct stat* statbuf);
	extern int fstatat(int dirfd, const char* path, struct stat* statbuf);
#endif

#endif /* _wh_header_posix_sys_stat_ */

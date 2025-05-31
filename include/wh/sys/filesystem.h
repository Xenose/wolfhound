#ifndef _wh_header_sys_filesystem_
#define _wh_header_sys_filesystem_

#include<wh/common.h>

typedef struct {
	wh_string_s name;
	u64 premissions;
} wh_dirfile_s;

typedef struct {
	u64 count;
	wh_dirfile_s* files;
} wh_dir_s;

typedef struct {
} _wh_dir_read_params;

#endif /* _wh_header_sys_filesystem_ */

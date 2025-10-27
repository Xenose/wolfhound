#ifndef _wh_header_sys_filesystem_
#define _wh_header_sys_filesystem_

#include<limits.h>
#include<wh/common.h>
#include<wh/types/memory.h>

WH_C()

enum {
	WH_FSYS_UNKNOWN,
	WH_FSYS_BLOCK,		// block device
	WH_FSYS_CHAR,		// Charter device
	WH_FSYS_DIR,		// directory
	WH_FSYS_FIFO,		// named pipe
	WH_FSYS_LINK,		// symbolic link
	WH_FSYS_FILE,		// normal file
	WH_FSYS_SOCKET,	// socket
};

typedef struct {
	char name[NAME_MAX];
	u8 type;
} wh_dir_entry_s;

typedef struct {
	u64 count;
	wh_dir_entry_s* entries;
} wh_dir_s;

typedef struct {
	wh_heap_header_s* heap;
	const char* path;
	i64* error;
} _wh_dir_read_params;


wh_dir_s _wh_read_dir(_wh_dir_read_params params);
void wh_dir_destroy(wh_heap_header_s* heap, wh_dir_s* dir);

#define wh_read_dir(...) _wh_read_dir((_wh_dir_read_params) { __VA_ARGS__ })

WH_C_END()
#endif /* _wh_header_sys_filesystem_ */

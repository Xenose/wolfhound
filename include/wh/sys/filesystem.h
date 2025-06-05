#ifndef _wh_header_sys_filesystem_
#define _wh_header_sys_filesystem_

#include<limits.h>
#include<wh/common.h>
#include<wh/types/memory.h>

WH_C

typedef struct {
	char name[NAME_MAX];
	u8 type;
} wh_dir_entry_s;

typedef struct {
	u64 count;
	wh_dir_entry_s* entries;
} wh_dir_s;

typedef struct {
} _wh_dir_read_params;


wh_dir_s wh_read_dir(wh_heap_header_s* heap, const char* path);
void wh_dir_destroy(wh_heap_header_s* heap, wh_dir_s* dir);

WH_C_END
#endif /* _wh_header_sys_filesystem_ */

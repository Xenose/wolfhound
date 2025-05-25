#ifndef _wh_header_file_
#define _wh_header_file_

#include<wh/common.h>

typedef struct {
	i64 length;

	union {
		void* ptr;
		i8* data;
		char* str;
	};
} wh_file_s;

typedef struct {
	const char* path;
} _wh_file_load_params;

typedef struct {
	wh_file_s file;
} _wh_file_unload_params;

extern wh_file_s _wh_file_load(_wh_file_load_params params);
extern i8 _wh_file_unload(_wh_file_unload_params params);

/* [MD_DOC]
 * # wh_file_load
 */
#define wh_file_load(...) _wh_file_load((_wh_file_load_params) { __VA_ARGS__ })
#define wh_file_unload(...) _wh_file_unload((_wh_file_unload_params) { __VA_ARGS__ })

#endif /* _wh_header_file_ */

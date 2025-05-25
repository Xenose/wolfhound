#ifndef _wh_header_params_library_
#define _wh_header_params_library_

#include<wh/types/library.h>

typedef struct {
	const char* filename;
	int flags;
} _wh_libopen_params;

typedef struct {
	wh_lib_s* lib; 
	const char* name;
	void** func;
} _wh_libget_params;

#endif /* _wh_header_params_library */

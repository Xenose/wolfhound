#ifndef _wh_header_window_
#define _wh_header_window_

#include<wh/common.h>
#include<wh/types/wolfhound.h>

typedef struct {
	wh_instance_s* ins;
	int* x;
	int* y;
} _wh_window_size_params;

//extern void _wh_window_get_size(_wh_window_size_params params);

//#define wh_window_get_size(...) _wh_window_get_size((_wh_window_size_params) { __VA_ARGS__ })

#endif /* _wh_header_window_ */

#ifndef _wh_header_params_wolfhound_
#define _wh_header_params_wolfhound_

#include<wh/common.h>
#include<wh/types/wolfhound.h>

typedef struct {
	wh_instance_s** ins;
	wh_args_s args;
	wh_string_s app_name;
	wh_string_s config_path;
	u64 heap_size;
	u64 mode_window;
	u64 mode_graphics;
	wh_config_s config;

	wh_heap_header_s* heap;
	wh_graphics_s*	grap;
} _wh_init_params;

typedef struct {
	wh_instance_s* instance;
	void (*update)(wh_instance_s* ins);
	void (*fixed_update)(wh_instance_s* ins);
} _wh_loop_params;

typedef struct {
	wh_instance_s* instance;
} _wh_end_params;


#endif /* _wh_header_params_wolfhound_ */

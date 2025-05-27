#include<wh/debug.h>
#include<wh/memory.h>
#include<wh/wolfhound.h>
#include<wh/vulkan.h>
#include<wh/string.h>
#include<wh/render.h>
#include<wh/signalar.h>
#include<wh/config.h>
#include<wh/raylib/raylib.h>

static i8 _wh_init_critical(_wh_init_params* params) {
	wh_signalar_init(params->args.ptr[0]);
	_wh_config_load(params, &params->ins->config);

	// Now we have somewhere to store our data
	params->ins->heap =
		wh_heap_init(params->ins->config.heap.size);
	
	params->ins->scratch = wh_heap_init(
		WH_1MB,
		params->heap, 
		WH_STRUCT_TYPE_HEAP_ARENA
	);
	// no longer needed
	//params->ins = wh_mem_alloc(&params->ins, sizeof(wh_instance_s));

	//if (nullptr == params->ins) {
	//	wh_log_error(("Failed to allocated instance!"));
	//	goto go_error_exit;
	//}

	// making a shortcut
	params->grap = &params->ins->graphics;
	params->grap->mode = params->mode;

	// loading libraries
	switch(params->mode) {
		case WH_GRAPHICS_MODE_RAYLIB: 
			wh_log_info(("Graphics mode sat to Raylib!"));
			_wh_raylib_init(); 
			break;
	}
	
	wh_log_init(params->mode);
	wh_log_info(("Done loading critical section!"));

	return 0;
go_error_exit:
	return -1;
}

wh_instance_s* _wh_init(_wh_init_params params) {
	#ifdef __clang__
		wh_log_debug(("Compiler used clang"));
	#elif defined(__GNUC__)
		wh_log_debug(("Compiler used gcc"));
	#endif

	// Critical functions that need to be loaded first
	if (-1 == _wh_init_critical(&params)) {
		wh_log_emergency(("Failed to init cirtical section"));
		goto go_error_exit;
	}
	
	// basic data init
	params.ins->stype = WH_STRUCT_TYPE_INSTANCE;
	params.ins->app_info.name = params.app_name;
	params.ins->app_info.engine = wh_string_create("wolfhound");

	wh_log_info(("Creating window!"));
	// Creating window in either SDL3 or Raylib
	if (-1 == wh_window_create(params.ins, 1920, 1080, (wh_string_s){ .str = "hello" })) {
		goto go_error_exit;
	}

	return params.ins;
go_error_exit:
	wh_end(params.ins);
	return  nullptr;
}

/* [MD_DOC]
 * The internal game engine loop.
 *
 */
void _wh_loop(_wh_loop_params params) {
	wh_instance_s* ins = params.instance;
	wh_graphics_s*	grap = &ins->graphics;

	wh_event_s event;

	if (ins->config.flags.dryrun) {
		event.code = WH_EVENT_WINDOW_CLOSE;
		goto go_skip_event_pull;
	}

go_loop:
	wh_event_pull(ins, &event);
go_skip_event_pull:

	if (nullptr != params.update) {
		params.update(ins);
	}

	switch (event.code) {
		case WH_EVENT_WINDOW_CLOSE:
			wh_log_info(("window is closing..."));
			break;
		default:
			goto go_loop;
	}
}

int64_t _wh_end(_wh_end_params params) {
	//SDL_DestroyWindow(params.instance->graphics.window.sdl);
	//SDL_Quit();

	// Free the instance pointer
	//wh_mem(0, params.instance);
	return 0;
}

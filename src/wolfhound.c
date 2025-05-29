#include<wh/debug.h>
#include<wh/memory.h>
#include<wh/wolfhound.h>
#include<wh/vulkan.h>
#include<wh/string.h>
#include<wh/render.h>
#include<wh/signalar.h>
#include<wh/config.h>
#include<wh/raylib/raylib.h>
#include<wh/wrap/unistd.h>
#include<wh/maths/memory.h>

static i8 _wh_init_critical(_wh_init_params* params) {
	wh_instance_s tmp;

	wh_signalar_init(params->args.ptr[0]);
	params->config = _wh_config_load(params, &params->config);

	// Now we have somewhere to store our data
	tmp.heap = wh_heap_init(params->config.heap.size);
	
	params->ins[0] = wh_mem_alloc(nullptr, sizeof(wh_instance_s));

	if (nullptr == params->ins[0]) {
		wh_log_error(("Failed to allocated instance!"));
		goto go_error_exit;
	}

	// we need to copy the instance from the stack to the
	// heap.
	memcpy(params->ins[0], &tmp, sizeof(wh_instance_s));
	memcpy(&params->ins[0]->config, &params->config, sizeof(wh_config_s));

	params->ins[0]->scratch = wh_heap_init(
		WH_1MB,
		params->heap, 
		WH_STRUCT_TYPE_HEAP_ARENA
	);

	// making a shortcut
	params->grap = &params->ins[0]->graphics;
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
	params.ins[0]->stype = WH_STRUCT_TYPE_INSTANCE;
	params.ins[0]->app_info.name = params.app_name;
	params.ins[0]->app_info.engine = wh_string_create("wolfhound");

	wh_log_info(("Creating window!"));
	// Creating window in either SDL3 or Raylib
	if (-1 == wh_window_create(params.ins[0], 1920, 1080, (wh_string_s){ .str = "hello" })) {
		goto go_error_exit;
	}

	return params.ins[0];
go_error_exit:
	wh_end(params.ins[0]);
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
	wh_render_clear(ins);

	if (nullptr != params.update) {
		params.update(ins);
	}
	
	wh_action_s* c = ins->game.actions;

	wh_for (u64, i, ins->game.action_count) {
		if (nullptr != c[i].act) {
			c[i].act(ins, &c[i]);
		}
	}

	if (nullptr != params.fixed_update) {
		params.fixed_update(ins);
	}
	
	wh_render_show(ins);

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

#include<wh/debug.h>
#include<wh/render.h>

extern void _wh_window_create_raylib(_wh_window_create_params params);
extern void _wh_event_pull_raylib(_wh_event_pull_params params);
extern void _wh_render_clear_raylib(_wh_render_clear_params params);
extern void _wh_render_show_raylib(_wh_render_show_params params);
extern void _wh_render_line_raylib(_wh_render_line_params params);


extern i8 _wh_window_create_sdl3(_wh_window_create_params params);
extern void _wh_render_clear_sdl3(_wh_render_clear_params params);
extern void _wh_event_pull_sdl3(_wh_event_pull_params params);
extern void _wh_render_show_sdl3(_wh_render_show_params params);
extern void _wh_render_line_sdl3(_wh_render_line_params params);

i8 _wh_window_create(_wh_window_create_params params) {
	wh_log_debug(("Rendering supports [ RAYLIB, SDL3, VULKAN ]"));

	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			wh_log_debug(("Selected [ RAYLIB ] rendering"));
			_wh_window_create_raylib(params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			wh_log_debug(("Selected [ SDL3 ] rendering"));
			_wh_window_create_sdl3(params);
			break;
	}
	return 0;
}

void _wh_window_get_size(_wh_window_get_size_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			break;
	}
}

void _wh_event_pull(_wh_event_pull_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_event_pull_raylib(params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			_wh_event_pull_sdl3(params);
			break;
	}
}

void _wh_render_clear(_wh_render_clear_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_render_clear_raylib(params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			_wh_render_clear_sdl3(params);
			break;
	}
}

void _wh_render_show(_wh_render_show_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_render_show_raylib(params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			_wh_render_show_sdl3(params);
			break;
	}
}

void _wh_render_line(_wh_render_line_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_render_line_raylib(params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			_wh_render_line_sdl3(params);
			break;
	}
}

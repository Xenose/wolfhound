#include<wh/debug/logger.h>
#include<wh/render.h>

extern i8 _wh_window_create_sdl3(_wh_window_create_params params);
extern void _wh_window_get_size_sdl3(_wh_window_get_size_params params);

extern void _wh_render_clear_sdl3(_wh_render_clear_params params);
extern void _wh_event_pull_sdl3(_wh_event_pull_params params);
extern void _wh_render_show_sdl3(_wh_render_show_params params);
extern void _wh_render_line_sdl3(_wh_render_line_params params);


const char* _wh_support_vulkan() {
#ifndef WH_VULKAN_NOT_FOUND
	return "VULKAN ";
#else
	return "";
#endif
}

i8 (*_wh_window_create)(_wh_window_create_params params)				= nullptr;
void (*_wh_window_get_size)(_wh_window_get_size_params params)		= nullptr;
void (*_wh_event_pull)(_wh_event_pull_params params)					= nullptr;
void (*_wh_render_clear)(_wh_render_clear_params params)				= nullptr;
void (*_wh_render_show)(_wh_render_show_params params)				= nullptr;
void (*_wh_render_line)(_wh_render_line_params params)				= nullptr;

i8 _wh_render_init(_wh_render_init_params params) {
	wh_log_info(("Init graphics stack"));

	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_SDL3:
			_wh_window_create			= &_wh_window_create_sdl3;
			_wh_window_get_size		= &_wh_window_get_size_sdl3;

			_wh_event_pull				= &_wh_event_pull_sdl3;

			_wh_render_clear			= &_wh_render_clear_sdl3;
			_wh_render_show			= &_wh_render_show_sdl3;
			_wh_render_line			= &_wh_render_line_sdl3;
			break;
	}

	if (nullptr == _wh_window_create)		goto go_error_exit;
	if (nullptr == _wh_window_get_size)		goto go_error_exit;

	if (nullptr == _wh_event_pull)			goto go_error_exit;

	if (nullptr == _wh_render_clear)			goto go_error_exit;
	if (nullptr == _wh_render_line)			goto go_error_exit;

	return 0;
go_error_exit:
	return -1;
}

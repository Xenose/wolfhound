#include<wh/debug/logger.h>
#include<wh/render.h>

#ifdef WH_SDL2_FOUND
	#include<wh-backend/sdl2.h>
#endif

#ifdef WH_GLFW_FOUND
	#include<wh-backend/glfw3.h>
#endif

#ifdef WH_SDL3_FOUND
	#include<wh-backend/sdl3.h>
#endif

const char* _wh_support_vulkan() {
#ifdef WH_VULKAN_FOUND
	return "VULKAN ";
#else
	return "";
#endif
}

void (*_wh_event_keys[8096])(wh_event_s* e) = {
	nullptr
};

i8 (*_wh_window_create)(_wh_window_create_params params)				= nullptr;
void (*_wh_window_get_size)(_wh_window_get_size_params params)		= nullptr;

void (*_wh_render_clear)(_wh_render_clear_params params)				= nullptr;
void (*_wh_render_show)(_wh_render_show_params params)				= nullptr;
void (*_wh_render_line)(_wh_render_line_params params)				= nullptr;

void (*_wh_event_pull)(_wh_event_pull_params params)					= nullptr;

i8 _wh_render_init(_wh_render_init_params params) {
	wh_log_info(("Init graphics stack"));
go_window_retry:
	switch(params.ins->graphics.mode_window) {
		case WH_WINDOW_MODE_GLFW:
#ifdef WH_GLFW_FOUND
			switch (params.ins->graphics.mode_graphics) {
				case WH_GRAPHICS_MODE_SDL2:
					wh_log_warning(("SDL2 graphics mode but backend set to GLFW3 switching window stack!"));
					params.ins->graphics.mode_window = WH_WINDOW_MODE_SDL2;
					goto go_window_retry;

				case WH_GRAPHICS_MODE_SDL3:
					wh_log_warning(("SDL3 graphics mode but backend set to GLFW3 switching window stack!"));
					params.ins->graphics.mode_window = WH_WINDOW_MODE_SDL3;
					goto go_window_retry;
			}

			_wh_window_create			= &_wh_window_create_glfw3;
			_wh_window_get_size		= &_wh_window_get_size_glfw3;
			_wh_event_pull				= &_wh_event_pull_glfw3;
			break;
#else
		wh_log_critical(("Engine not compiled with GLFW3!"));
		return -1;
#endif

		case WH_WINDOW_MODE_SDL2:
#ifdef WH_SDL2_FOUND
			_wh_window_create			= &_wh_window_create_sdl2;
			_wh_window_get_size		= &_wh_window_get_size_sdl2;
			_wh_event_pull				= &_wh_event_pull_sdl2;
			break;
#else
		#ifdef WH_SDL3_FOUND
			params.ins->graphics.mode_window = WH_WINDOW_MODE_SDL3;
			goto go_window_retry;
		#else
			wh_log_critical(("Engine not compiled with SDL2!"));
			return -1;
		#endif
#endif

		case WH_WINDOW_MODE_SDL3:
#ifdef WH_SDL3_FOUND
			_wh_window_create			= &_wh_window_create_sdl3;
			_wh_window_get_size		= &_wh_window_get_size_sdl3;
			_wh_event_pull				= &_wh_event_pull_sdl3;
			break;
#else
	#ifdef WH_SDL2_FOUND
		params.ins->graphics.mode_window = WH_WINDOW_MODE_SDL2;
		goto go_window_retry;
	#else
		wh_log_critical(("Engine not compiled with SDL3!"));
		return -1;
	#endif
#endif
	}

go_graphics_retry:
	switch(params.ins->graphics.mode_graphics) {
		case WH_GRAPHICS_MODE_SDL2:
#ifdef WH_SDL2_FOUND
			_wh_render_clear			= &_wh_render_clear_sdl2;
			_wh_render_show			= &_wh_render_show_sdl2;
			_wh_render_line			= &_wh_render_line_sdl2;
			break;
#else
		params.ins->graphics.mode_graphics = WH_GRAPHICS_MODE_SDL3;
		goto go_graphics_retry;
#endif

		case WH_GRAPHICS_MODE_SDL3:
#ifdef WH_SDL3_FOUND
			_wh_render_clear			= &_wh_render_clear_sdl3;
			_wh_render_show			= &_wh_render_show_sdl3;
			_wh_render_line			= &_wh_render_line_sdl3;
			break;
#else
		params.ins->graphics.mode_graphics = WH_GRAPHICS_MODE_SDL2;
		goto go_graphics_retry;
#endif
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

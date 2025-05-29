#include<wh/window.h>
#include<wh/raylib/window.h>

extern void _wh_window_get_size_sdl3(_wh_window_size_params* params);

void _wh_window_get_size(_wh_window_size_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_window_size_get_raylib(&params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			_wh_window_get_size_sdl3(&params);
			break;
	}
}

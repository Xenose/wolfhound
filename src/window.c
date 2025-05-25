#include<wh/window.h>
#include<wh/raylib/window.h>

void _wh_window_get_size(_wh_window_size_params params) {
	switch(params.ins->graphics.mode) {
		case WH_GRAPHICS_MODE_RAYLIB:
			_wh_window_size_get_raylib(&params);
			break;
		case WH_GRAPHICS_MODE_SDL3:
			break;
	}
}

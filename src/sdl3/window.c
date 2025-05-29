#include<wh/render.h>
#include<wh/window.h>

void _wh_window_get_size_sdl3(_wh_window_size_params* params) {
	SDL_GetWindowSize(params->ins->graphics.window.sdl, params->x, params->x);
}

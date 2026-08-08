#include<wh/render.h>
#include<wh/window.h>

#include<SDL2/SDL.h>

void _wh_window_get_size_sdl2(_wh_window_get_size_params params) {
	int x = 0;
	int y = 0;

	SDL_GetWindowSize(params.ins->graphics.window.sdl, &x, &y);

	*params.x = x;
	*params.y = y;
}

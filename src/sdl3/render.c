#include<SDL3/SDL.h>

#include<wh/debug.h>
#include<wh/render.h>

void _wh_render_clear_sdl3(_wh_render_clear_params params) {
	SDL_SetRenderDrawColor(
		params.ins->graphics.sdl3.renderer, 
		params.color.r, params.color.g, params.color.b, params.color.a);
	SDL_RenderClear(params.ins->graphics.sdl3.renderer);
}

void _wh_event_pull_sdl3(_wh_event_pull_params params) {
	SDL_Event event = { 0 };
	SDL_PollEvent(&event);
}

void _wh_render_show_sdl3(_wh_render_show_params params) {
	SDL_RenderPresent(params.ins->graphics.sdl3.renderer);
}

void _wh_render_line_sdl3(_wh_render_line_params params) {
	SDL_SetRenderDrawColor(params.ins->graphics.sdl3.renderer, params.color.r, params.color.g, params.color.b, params.color.a);

	SDL_FPoint* points = (void*)params.data;
	params.count /= 2;

	if (false == SDL_RenderLines(params.ins->graphics.sdl3.renderer, points, params.count)) {
		wh_log_error(("Failed to render line! [ %s ]"), SDL_GetError());
	}
}

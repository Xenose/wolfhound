#include<SDL2/SDL.h>

#include<wh/debug/logger.h>
#include<wh/render.h>

i8 _wh_window_create_sdl2(_wh_window_create_params params) {
	wh_graphics_s* grap = &params.ins->graphics;
	wh_log_debug(("Starting SDL2!"));

	grap->window.sdl = SDL_CreateWindow(params.title.str, (int)params.size_x, (int)params.size_y, 0, 0, 0);
	grap->sdl2.renderer = SDL_CreateRenderer(grap->window.sdl, 0, 0);

	return 0;
}

void _wh_render_clear_sdl2(_wh_render_clear_params params) {
	SDL_SetRenderDrawColor(
		params.ins->graphics.sdl2.renderer, 
		params.color.r, params.color.g, params.color.b, params.color.a);
	SDL_RenderClear(params.ins->graphics.sdl2.renderer);
}

void _wh_event_pull_sdl2(_wh_event_pull_params params) {
	SDL_Event event = { 0 };
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			params.event->code = WH_EVENT_WINDOW_CLOSE;
			break;
	}
}

/*void _wh_render_get_surface2(_wh_render_get_surface_params params) {
	params.ins->graphics.sdl2.surface =
		SDL_GetWindowSurface(params.ins->graphics.window.sdl);
}

void _wh_render_draw_pixel2(_wh_render_draw_pixel_params params) {
}*/

void _wh_render_show_sdl2(_wh_render_show_params params) {
	SDL_RenderPresent(params.ins->graphics.sdl3.renderer);
}

void _wh_render_line_sdl2(_wh_render_line_params params) {
	SDL_SetRenderDrawColor(params.ins->graphics.sdl3.renderer, params.color.r, params.color.g, params.color.b, params.color.a);

	SDL_FPoint* points = (void*)params.data;
	params.count /= 2;

	/*if (false == SDL_RenderDrawLines(params.ins->graphics.sdl3.renderer, points, (int)params.count)) {
		wh_log_error(("Failed to render line! [ %s ]"), SDL_GetError());
	}*/
}

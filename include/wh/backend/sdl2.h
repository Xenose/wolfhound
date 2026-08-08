#ifndef _wh_header_backend_sdl2_
#define _wh_header_backend_sdl2_

#include<wh/render.h>

extern i8 _wh_window_create_sdl2(_wh_window_create_params params);
extern void _wh_render_clear_sdl2(_wh_render_clear_params params);
extern void _wh_event_pull_sdl2(_wh_event_pull_params params);
//extern void _wh_render_get_surface(_wh_render_get_surface_params params);
//extern void _wh_render_draw_pixel(_wh_render_draw_pixel_params params);
extern void _wh_render_show_sdl2(_wh_render_show_params params);
extern void _wh_render_line_sdl2(_wh_render_line_params params);

extern void _wh_window_get_size_sdl2(_wh_window_get_size_params params);

#endif /* _wh_header_backend_sdl2_ */

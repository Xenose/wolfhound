#ifndef _wh_header_backend_sdl3_
#define _wh_header_backend_sdl3_

#include <wh/render.h>

extern i8 _wh_window_create_sdl3(_wh_window_create_params params);
extern void _wh_window_get_size_sdl3(_wh_window_get_size_params params);

extern void _wh_render_clear_sdl3(_wh_render_clear_params params);
extern void _wh_event_pull_sdl3(_wh_event_pull_params params);
extern void _wh_render_show_sdl3(_wh_render_show_params params);
extern void _wh_render_line_sdl3(_wh_render_line_params params);

#endif /* _wh_header_backend_sdl3_ */

#ifndef _wh_header_render_glfw3_
#define _wh_header_render_glfw3_

#include<wh/render.h>

extern i8 _wh_window_create_glfw3(_wh_window_create_params params);
extern void _wh_event_pull_glfw3(_wh_event_pull_params params);
extern void _wh_render_show_glfw3(_wh_render_show_params params);
extern void _wh_window_get_size_glfw3(_wh_window_get_size_params params);

#endif

#ifndef _wh_header_render_
#define _wh_header_render_

#include<wh/wolfhound.h>

enum {
	WH_EVENT_UNKOWN,
	WH_EVENT_WINDOW_CLOSE,
};

typedef struct {
	u64 code;
} wh_event_s;

// parameters
typedef struct {
	wh_instance_s* ins;
	i64 size_x;
	i64 size_y;
	wh_string_s title;
} _wh_window_create_params;

typedef struct {
	wh_instance_s* ins;
	i64* x;
	i64* y;
} _wh_window_get_size_params;

typedef struct {
	wh_instance_s* ins;
	wh_event_s* event;
} _wh_event_pull_params;

typedef struct {
	wh_instance_s* ins;
	wh_rgba_s color;
} _wh_render_clear_params;

typedef struct {
	wh_instance_s* ins;
} _wh_render_get_surface_params;

typedef struct {
	wh_instance_s* ins;
	int x;
	int y;
	wh_rgba_s color;
} _wh_render_draw_pixel_params;

typedef struct {
	wh_instance_s* ins;
} _wh_render_show_params;

typedef struct {
	wh_instance_s* ins;
	float* data;
	u64 count;
	wh_rgba_s color;
} _wh_render_line_params;

typedef struct {
	wh_instance_s* ins;
} _wh_render_init_params;

extern i8 (*_wh_window_create)(_wh_window_create_params params);
extern void (*_wh_event_pull)(_wh_event_pull_params params);

extern void (*_wh_render_clear)(_wh_render_clear_params params);
extern void (*_wh_render_show)(_wh_render_show_params params);
extern void (*_wh_render_line)(_wh_render_line_params params);

extern i8 _wh_render_init(_wh_render_init_params params);

/* [MD_DOC]
 * # wh_window_create
 */
#define wh_window_create(...) _wh_window_create((_wh_window_create_params) { __VA_ARGS__ })
#define wh_event_pull(...) _wh_event_pull((_wh_event_pull_params) { __VA_ARGS__ })

#define wh_render_clear(...) _wh_render_clear((_wh_render_clear_params) { __VA_ARGS__ })
#define wh_render_show(...) _wh_render_show((_wh_render_show_params) { __VA_ARGS__ })
#define wh_render_line(...) _wh_render_line((_wh_render_line_params) { __VA_ARGS__ })

#define wh_render_init(...) _wh_render_init((_wh_render_init_params) { __VA_ARGS__ })

#endif /* _wh_header_render_ */

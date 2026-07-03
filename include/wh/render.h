#ifndef _wh_header_render_
#define _wh_header_render_

#include<wh/wolfhound.h>

WH_C()

enum {
	WH_EVENT_UNKOWN,
	WH_EVENT_WINDOW_CLOSE,
};

typedef struct {
	wh_struct stype;
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


extern void (*_wh_event_keys[8096])(wh_event_s* e);

extern i8 (*_wh_window_create)(_wh_window_create_params params);
extern void (*_wh_window_get_size)(_wh_window_get_size_params params);
extern void (*_wh_event_pull)(_wh_event_pull_params params);

extern void (*_wh_render_clear)(_wh_render_clear_params params);
extern void (*_wh_render_show)(_wh_render_show_params params);
extern void (*_wh_render_line)(_wh_render_line_params params);

extern void _wh_event_subscribe(int key, void (*func)(wh_event_s*));

extern i8 _wh_render_init(_wh_render_init_params params);

/* [MD_DOC]
 * # wh_window_create
 */
#define wh_window_create(...)		WH_EPF(_wh_window_create((_wh_window_create_params) { __VA_ARGS__ }))
#define wh_window_get_size(...)	WH_EPF(_wh_window_get_size((_wh_window_get_size_params) { __VA_ARGS__ }))
#define wh_event_pull(...)			WH_EPF(_wh_event_pull((_wh_event_pull_params) { __VA_ARGS__ }))

#define wh_render_clear(...)	WH_EPF(_wh_render_clear((_wh_render_clear_params) { __VA_ARGS__ }))
#define wh_render_show(...)	WH_EPF(_wh_render_show((_wh_render_show_params) { __VA_ARGS__ }))
#define wh_render_line(...)	WH_EPF(_wh_render_line((_wh_render_line_params) { __VA_ARGS__ }))

#define wh_render_init(...)	WH_EPF(_wh_render_init((_wh_render_init_params) { __VA_ARGS__ }))

WH_C_END()
#endif /* _wh_header_render_ */

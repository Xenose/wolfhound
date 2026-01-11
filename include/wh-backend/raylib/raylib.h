#ifndef _wh_header_raylib_raylib_
#define _wh_header_raylib_raylib_

#include<stdarg.h>

#include<wh-common/common.h>

typedef enum {
	RAY_LOG_ALL,
	RAY_LOG_TRACE,
	RAY_LOG_DEBUG,
	RAY_LOG_INFO,
	RAY_LOG_WARNING,
	RAY_LOG_ERROR,
	RAY_LOG_FATAL,
	RAY_LOG_NONE,
} ray_trace_log_level;

typedef struct {
	u8 r : 8;
	u8 g : 8;
	u8 b : 8;
	u8 a : 8;
} ray_color_s;

typedef struct {
	void (*init_window)(int width, int height, const char* title);
	bool (*window_should_close)(void);
	void (*begin_drawing)(void);
	void (*clear_background)(ray_color_s color);
	void (*end_drawing)(void);
	void (*draw_line)(int x0, int y0, int x1, int y1, ray_color_s);
	void (*set_trace_log_callback)(void (*func)(int, const char*, va_list));
	int (*get_render_width)(void);
	int (*get_render_height)(void);
} raylib_l;

extern raylib_l raylib;
extern void _wh_raylib_init(void);

#ifndef WOLFHOUND_NO_MACROS
#endif 

#endif /* _wh_header_raylib_raylib_ */

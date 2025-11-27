//#include<raylib.h>
#include<wh/raylib/raylib.h>

#include<wh/debug/logger.h>
#include<wh/render.h>

i8 _wh_window_create_raylib(_wh_window_create_params params) {
	wh_log_debug(("Starting RAYLIB!"));
	raylib.init_window((int)params.size_x, (int)params.size_y, params.title.str);

	return 0;
}

void _wh_event_pull_raylib(_wh_event_pull_params params) {
	if (raylib.window_should_close()) {
		params.event->code = WH_EVENT_WINDOW_CLOSE;
	}
}

void _wh_render_clear_raylib(_wh_render_clear_params params) {
	raylib.begin_drawing();
	raylib.clear_background((ray_color_s){ params.color.r, params.color.g, params.color.b, params.color.a });
}

void _wh_render_show_raylib(_wh_render_show_params params) {
	raylib.end_drawing();
}

void _wh_render_line_raylib(_wh_render_line_params params) {
	float* p = params.data;
	ray_color_s c = { params.color.r, params.color.g, params.color.b, params.color.a };

	for (u64 i = 0; i < params.count / 4; i++) {
		// TODO normilze to int's
		raylib.draw_line((int)p[i], (int)p[i + 1], (int)p[i + 2], (int)p[i + 4], c);
	}
}

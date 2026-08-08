#include<wh/render.h>
#include<wh/window.h>
#include<wh/debug/logger.h>

#include<GLFW/glfw3.h>

void _wh_window_get_size_glfw3(_wh_window_get_size_params params) {
	int x = 0;
	int y = 0;

	glfwGetWindowSize(params.ins->graphics.window.glfw, &x, &y);

	*params.x = x;
	*params.y = y;
}

i8 _wh_window_create_glfw3(_wh_window_create_params params) {
	wh_graphics_s* grap = &params.ins->graphics;
	wh_log_debug(("Starting SDL3!"));

	grap->window.glfw = glfwCreateWindow((int)params.size_x, (int)params.size_y, params.title.str, nullptr, nullptr);
	glfwMakeContextCurrent(grap->window.glfw);
	return 0;
}


void _wh_event_pull_glfw3(_wh_event_pull_params params) {
	glfwPollEvents();
}

void _wh_render_show_glfw3(_wh_render_show_params params) {
	glfwSwapBuffers(params.ins->graphics.window.glfw);
}

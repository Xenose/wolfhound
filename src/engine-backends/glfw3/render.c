#include<GLFW/glfw3.h>

#include<wh/debug/logger.h>
#include<wh/render.h>

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

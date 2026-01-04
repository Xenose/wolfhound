#include<wh/render.h>
#include<wh/window.h>

#include<GLFW/glfw3.h>

void _wh_window_get_size_glfw3(_wh_window_get_size_params params) {
	int x = 0;
	int y = 0;

	glfwGetWindowSize(params.ins->graphics.window.glfw, &x, &y);

	*params.x = x;
	*params.y = y;
}

#include<wh/memory.h>
#include<wh/wolfhound.h>
#include<wh/print.h>
#include<wh/maths.h>
#include<wh/convert.h>
#include<wh/debug.h>
#include<wh/string.h>
#include<wh/render.h>
#include<wh/arg_parser.h>
#include<wh/raylib/raylib.h>
#include<wh/sys/library.h>
#include<wh/window.h>

void update(wh_instance_s* ins) {
	float square[] = {
		0.1,		0.15,		0.20,		0.15,
		0.20,		0.15,		0.20,		0.20,
		0.20,		0.20,		0.10,		0.20,
		0.10,		0.20,		0.10,		0.15,
	};

	i64 x = 1920;
	i64 y = 1080;
	int count = sizeof(square) / sizeof(float);

	//SDL_GetWindowSize(ins->graphics.window.sdl, &x, &y);

	wh_window_get_size(ins, &x, &y);

	wh_for(int, i, count) {
		if (i & 1) {
			square[i] *= y;
		} else {
			square[i] *= x;
		}
	}

	wh_render_clear(ins);
	wh_render_line(ins, square, count, { 255, 255, 255, 255 });
	wh_render_show(ins);
}

int main(int arc, char* const* arv) {
	//_wh_libfind("libraylib.so", (char*[]){ "/usr/lib", "/lib" }, 2);
	wh_instance_s ins = {};

	wh_init(
		&ins,
		(wh_args_s){ arc, arv },					// command line arguments
		wh_string_create("chess"),					// application name
		wh_string_create("./config.lua"),		// application config
		.mode = WH_GRAPHICS_MODE_RAYLIB
	);

	wh_loop(&ins, &update);
	wh_end(&ins);
go_error_exit:
	return 0;
}

#include<wh-sys/library.h>
#include<wh/backend/raylib/raylib.h>
#include<wh/debug/logger.h>

raylib_l raylib = { 0 };

void _wh_raylib_init(void) {
    u64 length = 0;
    wh_lib_s ray;

#if _WIN32
    ray = wh_libopen("raylib.dll", 0);
#else
    ray = wh_libopen("/usr/lib/libraylib.so", 0);
#endif

    // TODO make this cross platform
    /*if (nullptr == ray._linux) {
     * wh_log_critical(("Failed to load Raylib DLL"));
     * }*/

    void *funcs[] = {
        wh_libget(&ray, "InitWindow",				(void**) &raylib.init_window),
        wh_libget(&ray, "WindowShouldClose",	(void**) &raylib.window_should_close),
        wh_libget(&ray, "BeginDrawing",			(void**) &raylib.begin_drawing),
        wh_libget(&ray, "ClearBackground",		(void**) &raylib.clear_background),
        wh_libget(&ray, "EndDrawing",				(void**) &raylib.end_drawing),
        wh_libget(&ray, "DrawLine",				(void**) &raylib.draw_line),
        wh_libget(&ray, "SetTraceLogCallback", (void**) &raylib.set_trace_log_callback),
        wh_libget(&ray, "GetRenderWidth",		(void**) &raylib.get_render_width),
        wh_libget(&ray, "GetRenderHeight",		(void**) &raylib.get_render_height),
    };

    length = sizeof(funcs) / sizeof(void(*)(void));

    wh_for(u64, i, length) {
        if (nullptr == funcs[i]) {
            wh_log_warning(("Failed to load function pointer for raylib --> index : %d"), i + 1);
        } else {
            wh_log_debug(("loaded function pointer with index : %d"), i + 1);
        }
    }

    wh_log_notice(("Done loading Raylib"));
}

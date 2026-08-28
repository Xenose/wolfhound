#include <wh-posix/stdio.h>
#include <wh-posix/string.h>
#include <wh-sys/file.h>
#include <wh-sys/filesystem.h>
#include <wh-sys/info.h>
#include <wh-sys/library.h>
#include <wh-sys/memory.h>
#include <wh-types/gameinfo.h>
#include <wh/arg_parser.h>
#include <wh/backend/raylib/raylib.h>
#include <wh/convert.h>
#include <wh-sys/data/list.h>
#include <wh/debug/exceptions.h>
#include <wh/debug/logger.h>
#include <wh/game/actions.h>
#include <wh/game/entity.h>
#include <wh/images/loader.h>
#include <wh/maths/core.h>
#include <wh/print.h>
#include <wh/render.h>
#include <wh/string.h>
#include <wh/window.h>
#include <wh/wolfhound.h>

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

    wh_window_get_size(ins, &x, &y);

    wh_for(int, i, count) {
        if (i & 1) {
            square[i] *= y;
        } else {
            square[i] *= x;
        }
    }

    wh_render_line(ins, square, count, { 100, 255, 255, 255 });
}

void fixed_update(wh_instance_s* ins) {
}

i8 action_gravity(wh_instance_s* ins, wh_action_s* action) {
    return 0;
}

i8 action_collision(wh_instance_s* ins, wh_action_s* action) {
    return 0;
}

i8 action_health_gen(wh_instance_s* ins, wh_action_s* action) {
    return 0;
}

void disown_test() {
    void* a = wh_alloc(nullptr, 64, &a);
    wh_disown(nullptr, a, a);
}

int main(int arc, char* const* arv) {
    wh_print(("Testing floats -> %f\n"), 1.25f);

#if LINUX==WH_SYSTEM
    wh_log_debug(("The system is Linux!"));
#endif

    char buf[256] = { 0 };
    char img[256] = { 0 }; 

    wh_sys_program_path(buf, 255);
    wh_sys_program_path(img, 255);

    wh_strcat((buf, 256, strlen(buf)), "config.lua");
    wh_strcat((img, 256, strlen(img)), "test.lua");

    // wh_file_s imgf = wh_file_load(img);
    //	wh_image_decode(imgf);
    // wh_file_unload(imgf);

    //_wh_libfind("libraylib.so", (char*[]){ "/usr/lib", "/lib" }, 2);
    wh_instance_s* ins = wh_init(
        &ins,
        (wh_args_s){ 0, arc, arv },                         // command line arguments
        (wh_string_s){ .str = "chess", .length = 6},        // application name
        .mode_window   = WH_WINDOW_MODE_SDL3,
        .mode_graphics = WH_GRAPHICS_MODE_SDL3,
        .config_path   = (wh_string_s) { .str = buf, 0 },   // application config
    );

    //wh_list_s test_list = wh_dlist_init_memreq(int);

    /*wh_action_init(ins, 100);
      wh_entity_init(ins, 100);

      u64 gid = wh_action_register(ins, &action_gravity);
      u64 cid = wh_action_register(ins, &action_collision);
      u64 hgid = wh_action_register(ins, &action_health_gen);

      u64 wolf = wh_entity_create(ins, (wh_string_s){ .str = "wolf", .length = 5}, nullptr);

      wh_action_subscribe(ins, wolf, gid);
      wh_action_subscribe(ins, wolf, cid);
      wh_action_subscribe(ins, wolf, hgid);*/

    wh_heap_print();
    wh_loop(ins, &update, &fixed_update);

    wh_heap_print();
    disown_test();
    wh_heap_print();

    _wh_mem_scan();
    //_wh_mem_scan();
    wh_end(ins);
go_error_exit:
    return 0;
}

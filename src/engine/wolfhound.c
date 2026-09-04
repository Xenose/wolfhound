#include<wh-posix/string.h>
#include<wh-posix/unistd.h>
#include<wh-sys/foreman.h>
#include<wh-sys/memory.h>
#include<wh/config.h>
#include<wh-sys/debug/logger.h>
#include<wh/debug/signalar.h>
#include<wh/loader/asset.h>
#include<wh/maths/memory.h>
#include<wh/render.h>
#include<wh/string.h>
#include<wh/wolfhound.h>

#ifdef WH_VULKAN_FOUND
    #include <wh/backend/vulkan.h>
#endif

static void _wh_update_dummy(wh_instance_s* ins) {
}

static void _wh_fixed_update_dummy(wh_instance_s* ins) {
}

static i8 _wh_init_critical(_wh_init_params* params) {
    wh_instance_s tmp = { 0 };

    wh_signalar_init(params->args.ptr[0]);
    params->config = _wh_config_load(params, &params->config);
    tmp.heap = wh_heap_init("main", params->config.heap.size);

    // Allocating the memory to the user provided pointer
    *params->ins = wh_alloc(nullptr, sizeof(wh_instance_s), params->ins, WH_ALLOC_TAIL);

    if (nullptr == params->ins[0]) {
        wh_log_error(("Failed to allocated instance!"));
        goto go_error_exit;
    }

    // we need to copy the instance from the stack to the heap.
    memcpy(params->ins[0], &tmp, sizeof(wh_instance_s));
    memcpy(&params->ins[0]->config, &params->config, sizeof(wh_config_s));

    // making a shortcut
    params->grap = &params->ins[0]->graphics;

    params->grap->mode_window = params->mode_window;
    params->grap->mode_graphics = params->mode_graphics;

    wh_log_info(("Done loading critical section!"));
    return 0;
go_error_exit:
    return -1;
}

/* [MD_DOC]
 */
wh_instance_s* _wh_init(_wh_init_params params) {
    // Critical functions that need to be loaded first
    if (-1 == _wh_init_critical(&params)) {
        wh_log_emergency(("Failed to init cirtical section"));
        goto go_error_exit;
    }

    // basic data init
    (*params.ins)->stype = WH_STRUCT_TYPE_INSTANCE;
    (*params.ins)->app_info.name = params.app_name;
    (*params.ins)->app_info.engine = (wh_string_s){ .str = "wolfhound", .length = 9 };

    // loading assets
    wh_log_debug(("Loading game assets!"));
    _wh_assets_load("./resources"); // TODO :: this need a system overhaul

    wh_log_debug(("Started graphics section!"));
    if (-1 == wh_render_init(params.ins[0])) {
        wh_log_error(("Failed to load render functions!"));
        goto go_error_exit;
    }

    wh_log_info(("Creating window!"));
    // Creating window in either SDL3 or Raylib
    if (-1 == wh_window_create(params.ins[0], 1920, 1080, (wh_string_s){ .str = "hello" })) {
        goto go_error_exit;
    }

    wh_log_debug(("Graphics section over!"));
    return params.ins[0];
go_error_exit:
    wh_end(params.ins[0]);
    return  nullptr;
}

/* [MD_DOC]
 * The internal game engine loop.
 *
 */
void _wh_loop(_wh_loop_params params) {
    wh_instance_s* ins = params.instance;
    wh_graphics_s* grap = &ins->graphics;

    wh_event_s event = { 0 };

    if (nullptr == params.update) {
        params.update = &_wh_update_dummy;
    }

    if (nullptr == params.fixed_update) {
        params.fixed_update = &_wh_fixed_update_dummy;
    }
    
    wh_foreman_init(ins, &ins->foreman);
    
    if (ins->config.flags.dryrun) {
        event.code = WH_EVENT_WINDOW_CLOSE;
        goto go_skip_event_pull;
    }
go_loop:
    wh_event_pull(ins, &event);
go_skip_event_pull:
    wh_render_clear(ins);
    wh_foreman_execute(&ins->foreman);

    params.update(ins);

    wh_action_s* c = ins->game.actions;

    wh_for (u64, i, ins->game.action_count) {
        if (nullptr != c[i].act) {
            c[i].act(ins, &c[i]);
        }
    }

    params.fixed_update(ins);
    wh_render_show(ins);

    switch (event.code) {
        case WH_EVENT_WINDOW_CLOSE:
            wh_log_info(("window is closing..."));
            break;
        default:
            goto go_loop;
    }
}

int64_t _wh_end(_wh_end_params params) {
    //SDL_DestroyWindow(params.instance->graphics.window.sdl);
    //SDL_Quit();

    // Free the instance pointer
    //wh_mem(0, params.instance);
    return 0;
}

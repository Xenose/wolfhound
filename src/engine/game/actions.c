#include<wh-sys/debug/logger.h>
#include<wh/game/actions.h>

#include<wh-posix/string.h>

i8 _wh_action_init(_wh_action_init_params params) {
    u64 bytes = sizeof(wh_action_s) * params.count;

    params.ins->game.action_count = 0;
    params.ins->game.actions = wh_alloc(
            params.ins->heap, bytes, &params.ins->game.actions);

    if (nullptr == params.ins->game.actions) {
        wh_log_error(("Failed to allocate actions..."));
        goto go_error_exit;
    }

    memset(params.ins->game.actions, 0, bytes);
    return 0;
go_error_exit:
    return -1;
}

i8 _wh_action_register(_wh_action_register_params params) {
    u64 index = params.ins->game.action_count;

    wh_log_debug(("New action at index [ %i ]"), index);

    params.ins->game.actions[index].act = params.act;
    ++params.ins->game.action_count;
    return 0;
}

i8 _wh_action_subscribe(_wh_action_subscribe_params params) {
    return 0;
}

#ifndef _wh_header_game_actions_
#define _wh_header_game_actions_

#include<wh-core/common.h>
#include<wh-types/wolfhound.h>

typedef struct {
    wh_instance_s* ins;
    u64 count;
} _wh_action_init_params;

typedef struct {
    wh_instance_s* ins;
    i8 (*act) (struct _wh_instance_s* ins, struct _wh_action_s* action);
    void* ptr; // user provided
} _wh_action_register_params;

typedef struct {
    wh_instance_s* ins;
    u64 entity_id;
    u64 action_id;
} _wh_action_subscribe_params;

extern i8 _wh_action_init(_wh_action_init_params params);
extern i8 _wh_action_register(_wh_action_register_params params);
extern i8 _wh_action_subscribe(_wh_action_subscribe_params params);

#define wh_action_init(...) _wh_action_init((_wh_action_init_params) { __VA_ARGS__ })
#define wh_action_register(...) _wh_action_register((_wh_action_register_params) { __VA_ARGS__ })
#define wh_action_subscribe(...) _wh_action_subscribe((_wh_action_subscribe_params) { __VA_ARGS__ })

#endif /* _wh_header_game_actions_ */

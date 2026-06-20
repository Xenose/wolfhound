#include<wh-data/list.h>
#include<wh-posix/string.h>
#include<wh-sys/info.h>
#include<wh/game/actions.h>
#include<wh/game/entity.h>
#include<wh/print.h>
#include<wh/string.h>
#include<wh/wolfhound.h>
#include<wh/debug/logger.h>

void update(wh_instance_s* ins) {
}

void fixed_update(wh_instance_s* ins) {
}

i8 action_line_renderer(wh_instance_s* ins, wh_action_s* action) {
	return 0;
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

int main(int arc, char* const* arv) {
	wh_log_info(("Starting GameObject Demo!"));

	char buf[256] = { 0 };
	wh_instance_s* ins = { 0 };

	wh_sys_program_path(buf, 255);
	wh_strcat((buf, 256, strlen(buf)), "config.lua");

	ins = wh_init(
		&ins,
		(wh_args_s){ 0, arc, arv },										// command line arguments
		(wh_string_s){ .str = "gameobject", .length = 11},			// application name
		.mode_graphics = WH_GRAPHICS_MODE_SDL3,
		.config_path = (wh_string_s){ .str = buf, 0 },				// application config
	);

	wh_action_init(ins, 100);
	wh_entity_init(ins, 100);

	u64 gid = wh_action_register(ins, &action_gravity);
	u64 cid = wh_action_register(ins, &action_collision);
	u64 hgid = wh_action_register(ins, &action_health_gen);

	u64 wolf = wh_entity_create(ins, (wh_string_s){ .str = "wolf", .length = 5}, nullptr);

	wh_action_subscribe(ins, wolf, gid);
	wh_action_subscribe(ins, wolf, cid);
	wh_action_subscribe(ins, wolf, hgid);

	wh_loop(ins, &update, &fixed_update);

	return 0;
}

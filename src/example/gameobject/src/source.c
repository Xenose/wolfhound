#include<wh/wolfhound.h>
#include<wh/string.h>
#include<wh-sys/info.h>

int main(int arc, char* const* arv) {
	char buf[256] = { 0 };
	wh_instance_s* ins = { 0 };

	wh_sys_program_path(buf, 255);
	wh_strcat((buf, 256, strlen(buf)), "config.lua");

	ins = wh_init(
		&ins,
		(wh_args_s){ 0, arc, arv },										// command line arguments
		(wh_string_s){ .str = "gameobject", .length = 11},			// application name
		.mode = WH_GRAPHICS_MODE_SDL3,
		.config_path = (wh_string_s){ .str = buf, 0 },				// application config
	);

	return 0;
}

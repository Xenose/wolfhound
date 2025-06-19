#include<wh/memory.h>
#include<wh/wolfhound.h>
#include<wh/print.h>
#include<wh/maths/core.h>
#include<wh/convert.h>
#include<wh/debug/logger.h>
#include<wh/string.h>
#include<wh/render.h>
#include<wh/arg_parser.h>
#include<wh/raylib/raylib.h>
#include<wh/sys/library.h>
#include<wh/window.h>
#include<wh/game/entity.h>
#include<wh/types/gameinfo.h>
#include<wh/game/actions.h>
#include<wh/sys/info.h>
#include<wh/maths/core.h>
#include<wh/file.h>
#include<wh/images/loader.h>
#include<wh/sys/filesystem.h>
#include<wh/data/hashmap_lazy.h>

#include<stdio.h>

void update(wh_instance_s* ins) {
	float square[] = {
		0.1,		0.15,		0.20,		0.15,
		0.20,		0.15,		0.20,		0.20,
		0.20,		0.20,		0.10,		0.20,
		0.10,		0.20,		0.10,		0.15,
	};

	int x = 1920;
	int y = 1080;
	int count = sizeof(square) / sizeof(float);

	wh_window_get_size(ins, &x, &y);

	wh_for(int, i, count) {
		if (i & 1) {
			square[i] *= y;
		} else {
			square[i] *= x;
		}
	}

	wh_render_line(ins, square, count, { 255, 255, 255, 255 });
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

int main(int arc, char* const* arv) {
	wh_print(("Testing floats -> %f\n"), 1.25f);

	char buf[256] = { 0 };
	char img[256] = { 0 }; 
	wh_sys_program_path(buf, 255);
	wh_sys_program_path(img, 255);

	wh_strcat((buf, 256, strlen(buf)), "config.lua");
	wh_strcat((img, 256, strlen(img)), "test.lua");

	wh_file_s imgf = wh_file_load(img);
	wh_image_decode(imgf);
	wh_file_unload(imgf);

	//_wh_libfind("libraylib.so", (char*[]){ "/usr/lib", "/lib" }, 2);
	wh_instance_s* ins = wh_init(
		&ins,
		(wh_args_s){ 0,  arc, arv },					// command line arguments
		wh_string_create("chess"),						// application name
		(u8*)buf,											// application config
		.mode = WH_GRAPHICS_MODE_SDL3
	);

	wh_hashmap_lazy_s hml = _wh_hashmap_lazy_create(nullptr, 10, sizeof(int));

	wh_hashmap_lazy_insert(&hml, "test", (int[]){ 9 });
	wh_hashmap_lazy_insert(&hml, "test_from_me", (int[]){ 19 });
	wh_hashmap_lazy_insert(&hml, "test2", (int[]){ 8 });
	wh_hashmap_lazy_insert(&hml, "test3", (int[]){ 200 });
	wh_hashmap_lazy_insert(&hml, "test444", (int[]){ 900 });
	
	printf("Value is [ %i ]\n", *wh_hashmap_lazy_get(int*, &hml, "test"));
	printf("Value is [ %i ]\n", *wh_hashmap_lazy_get(int*, &hml, "test_from_me"));
	printf("Value is [ %i ]\n", *wh_hashmap_lazy_get(int*, &hml, "test2"));
	printf("Value is [ %i ]\n", *wh_hashmap_lazy_get(int*, &hml, "test3"));
	printf("Value is [ %i ]\n", *wh_hashmap_lazy_get(int*, &hml, "test444"));

	wh_action_init(ins, 100);
	u64 gid = wh_action_register(ins, &action_gravity);
	u64 cid = wh_action_register(ins, &action_collision);
	u64 hgid = wh_action_register(ins, &action_health_gen);

	u64 wolf = wh_entity_create(ins, wh_string_create("wolf"), nullptr);

	wh_action_subscribe(ins, wolf, gid);
	wh_action_subscribe(ins, wolf, cid);
	wh_action_subscribe(ins, wolf, hgid);

	wh_heap_print();
	wh_loop(ins, &update, &fixed_update);

	_wh_mem_scan();
	wh_end(ins);
go_error_exit:
	return 0;
}

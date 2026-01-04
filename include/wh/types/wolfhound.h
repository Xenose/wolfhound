#ifndef _wh_header_types_wolfhound_
#define _wh_header_types_wolfhound_

#include<wh/common.h>
#include<wh-sys/memory.h>

#include<wh/types/config.h>

#include<wh/types/gameinfo.h>

#if (!defined WH_SDL3_NOT_FOUND) && (!defined WH_SDL2_NOT_FOUND)
	#error SDL3 and SDL2 included at the same time.
#endif

#ifndef WH_VULKAN_NOT_FOUND
	#include<vulkan/vulkan.h>
#endif

enum {
	WH_WINDOW_MODE_SDL2,
	WH_WINDOW_MODE_SDL3,
	WH_WINDOW_MODE_GLFW,
};

enum {
	WH_GRAPHICS_MODE_CPU,
	WH_GRAPHICS_MODE_VULKAN,
	WH_GRAPHICS_MODE_SDL2,
	WH_GRAPHICS_MODE_SDL3,
	WH_GRAPHICS_MODE_OPENGL,
	WH_GRAPHICS_MODE_RAYLIB,
};

typedef struct {
	struct_type stype;
	int count;
	char* const* ptr;
} wh_args_s;

typedef struct {
	struct_type stype;
	wh_string_s name;
	wh_string_s engine;
} wh_app_info_s;


typedef struct {
#ifndef WH_VULKAN_NOT_FOUND
	struct_type			stype;
	VkInstance			instance;
	VkSurfaceKHR		surface;
	VkPhysicalDevice	physical;
	VkDevice				device;
#else
	void* nothing_here;
#endif
} wh_vulkan_s;

typedef struct {
	void* renderer;
	void* surface;
} wh_sdl3_s;

typedef struct {
	void* renderer;
	void* surface;
} wh_sdl2_s;

typedef struct {
	struct_type stype;
	u64 mode_window;
	u64 mode_graphics;
	
	union {
		void* sdl;
		void* glfw;
	} window;

	union {
		wh_vulkan_s vulkan;
		wh_sdl3_s sdl3;
		wh_sdl2_s sdl2;
	};
} wh_graphics_s;

typedef struct {
	struct_type stype;
} wh_worker_s;

typedef struct {
	struct_type stype;
} wh_foreman_s;

typedef struct {
	struct_type stype;
} wh_asset_handler_s;

typedef struct {
	struct_type stype;

	u64 action_count;
	wh_action_s* actions;

	u64 entity_count;
	wh_entity_s* entities;
	//wh_* entities;
	wh_heap_header_s* data;
} wh_game_s;

typedef struct _wh_instance_s {
	struct_type stype;
	wh_heap_header_s* heap;

	wh_config_s config;

	wh_app_info_s app_info;
	wh_graphics_s graphics;
	wh_asset_handler_s assets_handler;
	wh_game_s game;
} wh_instance_s;

#endif /* _wh_header_types_wolfhound_ */

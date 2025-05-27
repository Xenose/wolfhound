#ifndef _wh_header_types_wolfhound_
#define _wh_header_types_wolfhound_

#include<wh/common.h>
#include<wh/memory.h>

#include<wh/types/config.h>

#include<vulkan/vulkan.h>
#include<SDL3/SDL.h>

enum {
	WH_GRAPHICS_MODE_VULKAN,
	WH_GRAPHICS_MODE_SDL3,
	WH_GRAPHICS_MODE_RAYLIB,
};

typedef struct {
	int count;
	char* const* ptr;
} wh_args_s;

typedef struct {
	wh_string_s name;
	wh_string_s engine;
} wh_app_info_s;

typedef struct {
	VkInstance			instance;
	VkSurfaceKHR		surface;
	VkPhysicalDevice	physical;
	VkDevice				device;
} wh_vulkan_s;

typedef struct {
	SDL_Renderer* renderer;
} wh_sdl3_s;

typedef struct {
	u64 mode;
	
	union {
		SDL_Window* sdl;
	} window;
	
	union {
		wh_vulkan_s vulkan;
		wh_sdl3_s sdl3;
	};
} wh_graphics_s;

typedef struct {
	struct_type stype;
} wh_asset_handler_s;

typedef struct {
	struct_type stype;
	wh_heap_header_s* heap;
	wh_heap_header_s* scratch;

	wh_config_s config;

	wh_app_info_s app_info;
	wh_graphics_s graphics;
	wh_asset_handler_s assets_handler;
} wh_instance_s;

#endif /* _wh_header_types_wolfhound_ */

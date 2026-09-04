#include<SDL3/SDL_vulkan.h>
#include<wh-core/common.h>
#include<wh/backend/vulkan.h>
#include<wh-sys/debug/logger.h>

typedef struct {
	VkResult* res;
	wh_instance_s* ins;
	wh_graphics_s* grap;
	wh_vulkan_s* vk;
} _wh_vulkan_step_params;

static i64 _wh_init_vulkan_instance(_wh_vulkan_step_params* params) {
	u32 ext_count = 0;
	VkApplicationInfo app = { 0 };
	VkInstanceCreateInfo info = { 0 };

	wh_log_info(("Creating Instance"));
	const char* const* ext_names = SDL_Vulkan_GetInstanceExtensions(&ext_count);

	app = (VkApplicationInfo){
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = params->ins->app_info.name.str,
		.pEngineName = params->ins->app_info.engine.str
	};

	info = (VkInstanceCreateInfo){
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &app,
		.enabledExtensionCount = ext_count,
		.ppEnabledExtensionNames = ext_names
	};
	
	*params->res = vkCreateInstance(&info, nullptr, &params->vk->instance);

	if (VK_SUCCESS != *params->res) {
		wh_log_error(("Failed to create instance [ $v ]"), *params->res);
	}

	if (true != SDL_Vulkan_CreateSurface(
		params->grap->window.sdl, params->vk->instance, NULL, &params->vk->surface)) {
		wh_log_error(("Failed to create SDL surface"));
	}

	return *params->res;
}

static i64 _wh_queue_properties(u32* count, VkPhysicalDevice* dev, _wh_vulkan_step_params* params) {
	/*u32 support_surface = 0;
	VkQueueFamilyProperties fp[*count];

	vkGetPhysicalDeviceQueueFamilyProperties(*dev, count, fp);

	wh_for(u32, i, *count) {
		vkGetPhysicalDeviceSurfaceSupportKHR(*dev, i, params->vk->surface, &support_surface);
		wh_print(("hello\n"));

		wh_print((
			"\tQueue index [ %d ]\n"
			"\tGraphics    [ %s ]\n"
			"\tSurface     [ %s ]\n\n"
		),
			i, 
			VK_QUEUE_GRAPHICS_BIT & fp[i].queueFlags ? "TRUE" : "FALSE",
			support_surface ? "TRUE" : "FALSE"
		);
	}
*/
	return 0;
}

static i64 _wh_init_physical_device2(uint32_t count, _wh_vulkan_step_params* params) {
	/*u32 fq_count = 0;
	VkPhysicalDevice pd[count];
	VkPhysicalDeviceProperties pdp[count];

	*params->res = vkEnumeratePhysicalDevices(params->vk->instance, &count, pd);

	if (VK_SUCCESS != *params->res) {
		goto go_error_exit;
	}

	wh_for (u32, i, count) {
		vkGetPhysicalDeviceProperties(pd[i], &pdp[i]);
		vkGetPhysicalDeviceQueueFamilyProperties(pd[i], &fq_count, nullptr);

		wh_log_info(("Found devices [ %s ]\n"), pdp[i].deviceName);
		_wh_queue_properties(&fq_count, &pd[i], params);
	}

	// TODO select the best GPU
	params->vk->physical = pd[0];

go_error_exit:
	return *params->res;*/
	return 0;
}

/* [MD DOC]
 * # _wh_init_physical_device
 * This function is used to get the number of physical devices present
 * on our machine, then it will call _wh_init_physical_device2 to eval
 * the best candidate.
 *
 * | Name     | Type          | Description                          |
 * | -------- | ------------- | ------------------------------------ |
 * | instance | wh_instance_s | The instance of the wolfhound engine |
 *
 * ## Return value
 * This function returns the last VkResult value given.
 */
static int64_t _wh_init_physical_device(_wh_vulkan_step_params* params) {
	uint32_t count = 0;
	*params->res = vkEnumeratePhysicalDevices(params->vk->instance, &count, nullptr);

	if (VK_SUCCESS != *params->res) {
		goto go_error_exit;
	}

	return _wh_init_physical_device2(count, params);
go_error_exit:
	return *params->res;
}


/* [MD DOC]
 */
static i64 _wh_init_device(_wh_vulkan_step_params* params) {
	i64 result = 0;

	VkDeviceQueueCreateInfo qi = {
		VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		nullptr,
		0,
		0,
		0,
		0,
	};

	VkDeviceCreateInfo di = {
		VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		nullptr,
		0x0,
		// queues
		1,
		&qi,
		// layers
		0,
		NULL,
		// extensions
		0,
		NULL,
		// features
		0,
	};

	result = vkCreateDevice(params->vk->physical, &di, NULL, &params->vk->device);

	if (VK_SUCCESS != result) {
		wh_log_error(("Failed to create logical device [ $v ]\n"), result);
	}

	wh_log_info(("Created Vulkan logical device!"));
	return 0;
}

// ==========================================================================================================
//		Public facing functions
// ==========================================================================================================

i64 _wh_init_vulkan(_wh_init_vulkan_params params) {
	VkResult result = VK_SUCCESS;

	_wh_vulkan_step_params par = {
		.res = &result,
		.ins = params.instance,
		.grap = &params.instance->graphics
	};

	i64 (*fun[])(_wh_vulkan_step_params* params) = {
		&_wh_init_vulkan_instance,
		&_wh_init_physical_device,
		&_wh_init_device,
		NULL
	};

	if (NULL == params.instance) {
		wh_log_error(("Failure no Instance given!"));
		goto go_error_exit;
	}

	// Now we can access Vulkan directly
	par.vk = &par.ins->graphics.vulkan;



	for (i64 i = 0; NULL != fun[i]; i++) {
		fun[i](&par);
		
		if (VK_SUCCESS != result) {
			wh_log_error(("Failure to create instance! [ $v ]"), result);
			goto go_error_exit;
		}
	}

	wh_log_info(("Created Vulkan Instance! [ $v ]\n"), result);
	return 0;
go_error_exit:
	return -1;
}

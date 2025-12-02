#ifndef _wh_header_vulkan_
#define _wh_header_vulkan_

#include<wh/wolfhound.h>

typedef struct {
	wh_instance_s* instance;
} _wh_init_vulkan_params;

int64_t _wh_init_vulkan(_wh_init_vulkan_params params);

#define wh_init_vulkan(...) WH_EPF(_wh_init_vulkan((_wh_init_vulkan_params){ __VA_ARGS__ }))

#endif /* _wh_header_vulkan_ */

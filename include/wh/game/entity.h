#ifndef _wh_header_game_entity_
#define _wh_header_game_entity_

#include<wh/common.h>
#include<wh/types/wolfhound.h>

typedef struct {
	wh_instance_s* ins;
	u64 count;
} _wh_entities_init_params;

typedef struct {
	wh_instance_s* ins;
	wh_string_s name;
	void* data;
} _wh_entity_create_params;

extern i8 _wh_entity_init(_wh_entities_init_params params);
extern u64 _wh_entity_create(_wh_entity_create_params params);

#define wh_entity_init(...) _wh_entity_init((_wh_entities_init_params) { __VA_ARGS__ })
#define wh_entity_create(...) _wh_entity_create((_wh_entity_create_params) { __VA_ARGS__ })

#endif /* _wh_header_game_entity_ */

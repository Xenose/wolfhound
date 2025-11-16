#ifndef _wh_header_game_entity_
#define _wh_header_game_entity_

#include<wh/common.h>
#include<wh/types/wolfhound.h>

typedef struct {
	wh_instance_s* ins;
	u64 count;
} _wh_entities_init_params;

/* The Action Entity system idea
 * [ header render info ]
 * [ header positions ]
 * [ header velocity  ]
 * ....
 * [ data render info ]
 * [ data position ]
 * [ data velocity ]
 */
typedef struct {
	wh_instance_s* ins;
	wh_string_s name;
	void* data;
} _wh_entity_create_params;

typedef struct {
	struct_type stype;
	atomic_flag locked;
	u64 data_type;
	i64 row_count;
	void* data_start;
} wh_entity_data_header_s;

typedef struct {
	struct_type stype;
	atomic_flag locked;
	u64 count;
	wh_entity_data_header_s* headers;
} wh_entity_s;

extern i8 _wh_entity_init(_wh_entities_init_params params);
extern u64 _wh_entity_create(_wh_entity_create_params params);

#define wh_entity_init(...) _wh_entity_init((_wh_entities_init_params) { __VA_ARGS__ })
#define wh_entity_create(...) _wh_entity_create((_wh_entity_create_params) { __VA_ARGS__ })

#endif /* _wh_header_game_entity_ */

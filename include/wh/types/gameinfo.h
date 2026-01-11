#ifndef _wh_header_types_gameinfo_
#define _wh_header_types_gameinfo_

#include<wh-common/common.h>

enum {
	WH_DATA_HEADER_START,
	WH_DATA_HEADER_MODEL,
	WH_DATA_HEADER_POSITION,

	WH_DATA_HEADER_END_OF_ENUM,
};

struct _wh_instance_s;

typedef struct {
	void* nil;
} wh_scene_s;

typedef struct {
	void* nil;
} wh_region_s;

typedef struct {
	void* nil;
} wh_chunk_s;

// IDEA
// action -> gameobject -> data

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
	struct_type stype;
	atomic_flag locked;
	u64 var_type;
	u64 row_count;
	void* data_start;
} wh_entity_data_header_s;

typedef struct {
	struct_type stype;
	atomic_flag locked;
	u64 count;
	wh_entity_data_header_s* headers;
} wh_entity_s;

/*typedef struct {
	wh_struct stype;
	u64 type;
	atomic_flag lock;
	void* start;
	void* end;
} wh_data_header_s;

typedef struct {
	wh_struct stype;
	u64 id;
	wh_string_s name;
	void* data;
} wh_entity_s;*/

typedef struct _wh_action_s {
	wh_struct stype;
	i8 (*act) (struct _wh_instance_s* ins, struct _wh_action_s* action);
	// how many gameobjects this action should have
	u64 hash_count;
	u64* hashes;

	wh_entity_s* entities;
} wh_action_s;


#endif /* _wh_header_types_gameinfo_ */

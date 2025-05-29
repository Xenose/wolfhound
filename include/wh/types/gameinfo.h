#ifndef _wh_header_types_gameinfo_
#define _wh_header_types_gameinfo_

#include<wh/common.h>

enum {
	WH_DATA_HEADER_START,
	WH_DATA_HEADER_MODEL,
	WH_DATA_HEADER_POSITION,

	WH_DATA_HEADER_END_OF_ENUM,
};

struct _wh_instance_s;

typedef struct {
} wh_scene_s;

typedef struct {
} wh_region_s;

typedef struct {
} wh_chunk_s;

// IDEA
// action -> gameobject -> data

typedef struct {
	wh_struct stype;
	u64 type;
	void* start;
	void* end;
} wh_data_header_s;

typedef struct {
	wh_struct stype;
	u64 id;
	wh_string_s name;
	wh_data_header_s* data;
} wh_entity_s;

typedef struct _wh_action_s {
	wh_struct stype;
	i8 (*act) (struct _wh_instance_s* ins, struct _wh_action_s* action);
	// how many gameobjects this action should have
	u64 hash_count;
	u64* hashes;

	wh_entity_s* entities;
} wh_action_s;


#endif /* _wh_header_types_gameinfo_ */

#ifndef _wh_header_types_gameinfo_
#define _wh_header_types_gameinfo_

#include<wh/common.h>

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
	u64 count;
	void* ptr;
} wh_data_s;

typedef struct {
	wh_struct stype;

	// array index
	u64 hash;

	// this structs name
	wh_string_s name;
} wh_gameobject_s;

typedef struct {
	wh_struct stype;

	// how many gameobjects this action should have
	u64 hash_count;
	u64* hashes;

	void (*run)(wh_gameobject_s* gameobject);
} wh_action_s;

#endif /* _wh_header_types_gameinfo_ */

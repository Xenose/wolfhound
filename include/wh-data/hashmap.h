#ifndef _wh_header_data_hashmap_
#define _wh_header_data_hashmap_

#include<wh-common/common.h>

// Constant key hashmap
// needs to live for the scope of the hashmap
typedef struct {
	void* data;
	char* key;
} wh_hashmap_slot_string_s;

// Fixed sized key hashmap
// cannot be longer then the key array
typedef struct {
	void* data;
	char key[32];
} wh_hashmap_slot_string32_s;

typedef struct {
	void* data;
	char key[64];
} wh_hashmap_slot_string64_s;

typedef struct {
	void* data;
	char key[128];
} wh_hashmap_slot_string128_s;

// Numeric hashmap's
typedef struct {
	void* data;
	i32 key;
} wh_hashmap_slot_i32_s;

typedef struct {
	void* data;
	i64 key;
} wh_hashmap_slot_i64_s;

// Data container struct
typedef struct {
	struct_type stype;
	void* slots;

	u64 type_size;
	u64 slot_count;
	u64 resize_size;
} wh_hashmap_s;

typedef struct {
	struct_type stype;
	u64 type_size;
	u64 init_size;
} _wh_hashmap_init_params;

extern wh_hashmap_s _wh_hashmap_init(_wh_hashmap_init_params params);

extern i8 _wh_hashmap_insert(wh_hashmap_s* map, void* key, void* value);

#define wh_hashmap_init()
#define wh_hashmap_clear()
#define wh_hashmap_resize()
#define wh_hashmap_destroy()

#define wh_hashmap_remove()
#define wh_hashmap_insert() _wh_hashmap_insert(wh_hashmap_s* map, void* key, void* value)
#define wh_hashmap_get()

#define wh_hashmap_foreach()

#define wh_hashmap_init_mmap_lazy(...) WH_EPF(_wh_hashmap_init((_wh_hashmap_init_params ) { WH_STRUCT_TYPE_HASHMAP_LAZY_STRING_SYS, __VA_ARGS__ }))

#endif /* _wh_header_data_hashmap_ */

#ifndef _wh_header_types_config_
#define _wh_header_types_config_

#include<wh/common.h>

typedef struct {
	u8 dryrun				: 1;
	u8 memory_tracking	: 1;
	u8 run_tests			: 1;
	u8 log_debug			: 1; 
	u8 log_info				: 1; 
	u8 log_notice			: 1;
	u8 log_warning			: 1;
	u8 log_error			: 1;
	u8 log_critical		: 1;
	u8 log_alert			: 1;
	u8 log_emergency		: 1;
} wh_config_flags_s;

typedef struct {
	u64 size;
} wh_config_heap_s;

typedef struct {
	wh_string_s game_name;

	wh_config_heap_s heap;
	wh_config_flags_s flags;
} wh_config_s;

#endif /* _wh_header_types_config_ */

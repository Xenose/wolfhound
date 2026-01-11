#ifndef _wh_header_types_assets_
#define _wh_header_types_assets_

#include<wh-common/common.h>

typedef struct {
	struct_type stype;
	u64 id;
	wh_string_s name;
	wh_buffer_s data;
} wh_asset_s;

#endif /* _wh_header_types_assets_ */

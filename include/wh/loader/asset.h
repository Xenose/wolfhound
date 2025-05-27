#ifndef _wh_header_asset_loader_
#define _wh_header_asset_loader_

#include<wh/common.h>

typedef struct {
	struct_type stype;
	u64 id;
	wh_string_s name;
	wh_buffer_s data;
} wh_asset_s;

#endif /* _wh_header_asset_loader_ */

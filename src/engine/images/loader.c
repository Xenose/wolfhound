#include<wh/debug/logger.h>
#include<wh/images/loader.h>
#include<wh-sys/file.h>

i8 _wh_image_decode(_wh_image_decode_params params) {
	int type = 0;

	type = _wh_file_type(nullptr, params.file.ptr, params.file.length);

	switch(type) {
		case WH_FILE_TYPE_PNG:
			wh_log_debug(("Found a PNG!"));
			break;
		default:
			wh_log_debug(("Unknown file type :("));
	}

	return 0;
}

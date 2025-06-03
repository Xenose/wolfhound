#ifndef _wh_header_images_loader_
#define _wh_header_images_loader_

#include<wh/common.h>
#include<wh/file.h>

typedef struct {
	wh_file_s file;
} _wh_image_decode_params;

typedef struct {
	u64 bytes;
	union {
		void* ptr;
		u8* data;
	};
} wh_image_s;

extern i8 _wh_image_decode(_wh_image_decode_params params);

#define wh_image_decode(...) _wh_image_decode((_wh_image_decode_params) { __VA_ARGS__ })

#endif /* _wh_header_images_loader_ */

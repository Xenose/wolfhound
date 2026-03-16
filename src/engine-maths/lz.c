#include<wh-posix/string.h>
#include<wh-maths/lz.h>


typedef struct {
	wh_buffer_s* const in;
	wh_buffer_s* out;
} wh_lz_params;

typedef struct {
	wh_struct stype;
	u64 content_size;
	u32 dictornary_id;
	u8 flg;
	u8 db;
	u8 hc;
} wh_lz4_header_s;


i64 wh_lz4_encode(wh_lz_params params) {
	wh_buffer_s* in = params.in;
	wh_buffer_s* out = params.out;

	if (nullptr == params.in || nullptr == params.out) {
		goto go_error_exit;
	}

	memcpy(out->ptr, WH_U32(0x184D2204), 4);

	for (u64 i = 4; i < in->bytes; i++) {
	}

	return 0;
go_error_exit:
	return -1;
}

i64 wh_lz4_decode(wh_lz_params params) {
	wh_buffer_s* in = params.in;
	wh_buffer_s* out = params.out;

	u64 offset = 0;
	wh_lz4_header_s header = { 0 };

	if (nullptr == params.in || nullptr == params.out) {
		goto go_error_exit;
	}

	header.flg = *(u8*)wh_ptr_offset(in->ptr, 4);
	header.db  = *(u8*)wh_ptr_offset(in->ptr, 5) & 0x01110000;

	// Checking LZ4 version
	if (0x01000000 & ~header.flg) {
		goto go_error_exit;
	}

	// if this bit is set the content length is included
	if (0x00001000 & header.flg) {
		header.content_size = *(u64*)wh_ptr_offset(in->ptr, 6);
		offset += 8;

		if (out->bytes < header.content_size) {
			goto go_error_exit;
		}
	}

	if (0x00000100 & header.flg) {
		header.content_size = *(u64*)wh_ptr_offset(in->ptr, offset + 6);
		offset += 4;
	}

	header.hc = *(u8*)wh_ptr_offset(in->ptr, offset + 6);

	for (u64 i = 0; i < in->bytes; i++) {
	}

	return 0;
go_error_exit:
	return -1;
}

i64 wh_lz77(wh_lz_params params) {
	return 0;
}


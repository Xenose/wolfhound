#ifndef _wh_header_file_
#define _wh_header_file_

#ifdef _WIN32
	#include<wh-posix/windows.h>
#endif

#include<wh/common.h>

enum {
	WH_FILE_TYPE_UNKNOWN,

	WH_FILE_TYPE_7Z,
	WH_FILE_TYPE_AVI,
	WH_FILE_TYPE_BMP,
	WH_FILE_TYPE_WASM,
	WH_FILE_TYPE_WEBP,
	WH_FILE_TYPE_CAB,
	WH_FILE_TYPE_COM,
	WH_FILE_TYPE_CR2,
	WH_FILE_TYPE_CR3,
	WH_FILE_TYPE_DAT,
	WH_FILE_TYPE_DER,
	WH_FILE_TYPE_DJV,
	WH_FILE_TYPE_EXE,
	WH_FILE_TYPE_FITS,
	WH_FILE_TYPE_FLIF,
	WH_FILE_TYPE_FLV,
	WH_FILE_TYPE_GIF,
	WH_FILE_TYPE_GZIP,
	WH_FILE_TYPE_ISO,
	WH_FILE_TYPE_IWAD,
	WH_FILE_TYPE_JPEG,
	WH_FILE_TYPE_JPEG2K,
	WH_FILE_TYPE_LUA_BYTECODE,
	WH_FILE_TYPE_LZ4,
	WH_FILE_TYPE_LZIP,
	WH_FILE_TYPE_MLV,
	WH_FILE_TYPE_MP3,
	WH_FILE_TYPE_NES,
	WH_FILE_TYPE_OAR,
	WH_FILE_TYPE_OGG,
	WH_FILE_TYPE_OPENSSH_PRIVATE,
	WH_FILE_TYPE_OPENSSH_PUBLIC,
	WH_FILE_TYPE_PBM_ASCII,
	WH_FILE_TYPE_PBM_BINARY,
	WH_FILE_TYPE_PDF,
	WH_FILE_TYPE_PGM_ASCII,
	WH_FILE_TYPE_PGM_BINARY,
	WH_FILE_TYPE_PNG,
	WH_FILE_TYPE_PPM_ASCII,
	WH_FILE_TYPE_PPM_BINARY,
	WH_FILE_TYPE_PWAD,
	WH_FILE_TYPE_RAR,
	WH_FILE_TYPE_SHELL,
	WH_FILE_TYPE_STG,
	WH_FILE_TYPE_T64,
	WH_FILE_TYPE_TAR,
	WH_FILE_TYPE_TEXT_U8,
	WH_FILE_TYPE_TIFF,
	WH_FILE_TYPE_WAV,
	WH_FILE_TYPE_WEBM,
	WH_FILE_TYPE_XZ,
};

#ifdef _WIN32
typedef struct {
	HANDLE h_fd;		// file handle from CreateFile
	HANDLE h_map;		// mapping handle from CreateFileMapping
} _wh_file_windows_s;
#endif

typedef struct {
	i64 length;

	union {
		void* ptr;
		i8* data;
		char* str;
	};

#ifdef _WIN32
	_wh_file_windows_s _windows;
#endif
} wh_file_s;

typedef struct {
	const char* path;
	int* error;
} _wh_file_load_params;

typedef struct {
	wh_file_s file;
} _wh_file_unload_params;

extern i64 _wh_file_type(const char* restrict filename, u8* restrict buffer, u64 length);
extern wh_file_s _wh_file_load(_wh_file_load_params params);
extern i8 _wh_file_unload(_wh_file_unload_params params);

/* [MD_DOC]
 * # wh_file_load
 */
#define wh_file_load(...) WH_EPF(_wh_file_load((_wh_file_load_params) { __VA_ARGS__ }))
#define wh_file_unload(...) WH_EPF(_wh_file_unload((_wh_file_unload_params) { __VA_ARGS__ }))

#endif /* _wh_header_file_ */

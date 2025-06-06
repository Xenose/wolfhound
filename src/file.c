#include<fcntl.h>
#include<wh/file.h>
#include<wh/debug.h>

#include<errno.h>

#include<string.h>

typedef struct {
	u64 type;
	u64 length;
	u8* signature;
	char** extensions;
	u8* mask;
} _wh_file_type_s;

_wh_file_type_s formats[] = {
	{ WH_FILE_TYPE_OPENSSH_PRIVATE,	32, (u8[]){ 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x42, 0x45, 0x47, 0x49, 0x4E, 0x20, 0x4F, 0x50, 0x45, 0x4E, 0x53, 0x53, 0x48, 0x20, 0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x20, 0x4B, 0x45, 0x59, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D}},
	{ WH_FILE_TYPE_FITS,					26, (u8[]){ 0x53, 0x49, 0x4D, 0x50, 0x4C, 0x45, 0x20, 0x20, 0x3D, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x54 },														(char*[]){ ".fits",																							nullptr }},
	{ WH_FILE_TYPE_OPENSSH_PUBLIC,	23, (u8[]){ 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x42, 0x45, 0x47, 0x49, 0x4E, 0x20, 0x53, 0x53, 0x48, 0x32, 0x20, 0x4B, 0x45, 0x59, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D },																										(char*[]){ ".pub",																							nullptr }},
	{ WH_FILE_TYPE_T64,					19, (u8[]){ 0x43, 0x36, 0x34, 0x20, 0x74, 0x61, 0x70, 0x65, 0x20, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x20, 0x66, 0x69, 0x6C, 0x65 },																																				(char*[]){ ".t64",																							nullptr }},
	{ WH_FILE_TYPE_DJV,					12, (u8[]){ 0x41, 0x54, 0x26, 0x54, 0x46, 0x4F, 0x52, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x44, 0x4A, 0x56 },																																												(char*[]){ ".djv", ".djvu",																				nullptr }, (u8[]){ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF } },
	{ WH_FILE_TYPE_WAV,					12, (u8[]){ 0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45 },																																																		(char*[]){ ".wav",																							nullptr }, (u8[]){ 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF }},
	{ WH_FILE_TYPE_AVI,					12, (u8[]){ 0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x41, 0x56, 0x49, 0x20 },																																																		(char*[]){ ".avi",																							nullptr }, (u8[]){ 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF } },
	{ WH_FILE_TYPE_WEBP,					11, (u8[]){ 0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x45, 0x42, 0x50 },																																																				(char*[]){ ".webp",																							nullptr }, (u8[]){ 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF }},
	{ WH_FILE_TYPE_CR2,					10, (u8[]){ 0x49, 0x49, 0x2A, 0x00, 0x10, 0x00, 0x00, 0x00, 0x43, 0x52 },																																																						(char*[]){ ".cr2",																							nullptr }},	// Cannon Raw 2
	{ WH_FILE_TYPE_CR3,					9,  (u8[]){ 0x66, 0x74, 0x79, 0x70, 0x63, 0x72, 0x78, 0x43, 0x52 },																																																								(char*[]){ ".cr3",																							nullptr }},	// Cannon Raw 3
	{ WH_FILE_TYPE_JPEG,					8,  (u8[]){ 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46 },																																																										(char*[]){ ".jpeg", ".jpg",																				nullptr }},
	{ WH_FILE_TYPE_DAT,					8,  (u8[]){ 0x50, 0x4D, 0x4F, 0x43, 0x43, 0x4D, 0x4F, 0x43 },																																																										(char*[]){ ".dat",																							nullptr }},
	{ WH_FILE_TYPE_TAR,					8,  (u8[]){ 0x75, 0x73, 0x74, 0x61, 0x72, 0x00, 0x30, 0x30 },																																																										(char*[]){ ".tar",																							nullptr }},
	{ WH_FILE_TYPE_TAR,					8,  (u8[]){ 0x75, 0x73, 0x74, 0x61, 0x72, 0x20, 0x20, 0x00 },																																																										(char*[]){ ".tar",																							nullptr }},
	{ WH_FILE_TYPE_JPEG2K,				8,  (u8[]){ 0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50, 0x20, 0x20 },																																																										(char*[]){ ".jp2", ".j2k", ".jpf", ".jpm.", ".jpg2", ".j2c", ".jpc", ".jpx", ".mj2",	nullptr }},
	{ WH_FILE_TYPE_PNG,					8,  (u8[]){ 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A },																																																										(char*[]){ ".png",																							nullptr }},
	{ WH_FILE_TYPE_RAR,					7,  (u8[]){ 0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x01, 0x00 },																																																										(char*[]){ ".rar",																							nullptr }},
	{ WH_FILE_TYPE_RAR,					6,  (u8[]){ 0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00},																																																												(char*[]){ ".rar",																							nullptr }},
	{ WH_FILE_TYPE_7Z,					6,  (u8[]){ 0x37, 0x7A, 0xBC, 0xAF, 0x27, 0x1C },																																																														(char*[]){ ".7z",																								nullptr }},
	{ WH_FILE_TYPE_GIF,					6,  (u8[]){ 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 },																																																														(char*[]){ ".gif",																							nullptr }},
	{ WH_FILE_TYPE_GIF,					6,  (u8[]){ 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 },																																																														(char*[]){ ".gif",																							nullptr }},
	{ WH_FILE_TYPE_XZ,					6,  (u8[]){ 0xFD, 0x37, 0x7A, 0x58, 0x5A, 0x00 },																																																														(char*[]){ ".xz", "tar.xz",																				nullptr }},
	{ WH_FILE_TYPE_PDF,					5,  (u8[]){ 0x25, 0x50, 0x44, 0x46, 0x2D },																																																																(char*[]){ ".pdf",																							nullptr }},
	{ WH_FILE_TYPE_ISO,					5,  (u8[]){ 0x43, 0x44, 0x30, 0x30, 0x31 },																																																																(char*[]){ ".iso",																							nullptr }},
	{ WH_FILE_TYPE_CAB,					4,  (u8[]){ 0x4D, 0x53, 0x43, 0x46 },																																																																		(char*[]){ ".cab",																							nullptr }},
	{ WH_FILE_TYPE_FLIF,					4,  (u8[]){ 0x46, 0x4C, 0x49, 0x46 },																																																																		(char*[]){ ".flif",																							nullptr }},
	{ WH_FILE_TYPE_LUA_BYTECODE,		4,  (u8[]){ 0x1B, 0x4C, 0x75, 0x61 }},	// lua byte code
	{ WH_FILE_TYPE_LZ4,					4,  (u8[]){ 0x04, 0x22, 0x4D, 0x18 },																																																																		(char*[]){ ".lz4",																							nullptr }},
	{ WH_FILE_TYPE_STG,					4,  (u8[]){ 0x4D, 0x49, 0x4C, 0x20 },																																																																		(char*[]){ ".stg",																							nullptr }},
	{ WH_FILE_TYPE_LZIP,					4,  (u8[]){ 0x4C, 0x5A, 0x49, 0x50 }},	// lzip
	{ WH_FILE_TYPE_MLV,					4,  (u8[]){ 0x4D, 0x4C, 0x56, 0x49 },																																																																		(char*[]){ ".mlv",																							nullptr }},
	{ WH_FILE_TYPE_OGG,					4,  (u8[]){ 0x4F, 0x67, 0x67, 0x53 },																																																																		(char*[]){ ".ogg", ".oga", ".ogv",																		nullptr }},
	{ WH_FILE_TYPE_TIFF,					4,  (u8[]){ 0x49, 0x49, 0x2A, 0x00 },																																																																		(char*[]){ ".tiff", ".tif",																				nullptr }},
	{ WH_FILE_TYPE_TIFF,					4,  (u8[]){ 0x49, 0x49, 0x2B, 0x00 },																																																																		(char*[]){ ".tiff", ".tif",																				nullptr }},
	{ WH_FILE_TYPE_TIFF,					4,  (u8[]){ 0x4D, 0x4D, 0x00, 0x2A },																																																																		(char*[]){ ".tiff", ".tif",																				nullptr }},
	{ WH_FILE_TYPE_TIFF,					4,  (u8[]){ 0x4D, 0x4D, 0x00, 0x2B },																																																																		(char*[]){ ".tiff", ".tif",																				nullptr }},
	{ WH_FILE_TYPE_IWAD,					4,  (u8[]){ 0x49, 0x57, 0x41, 0x44 },																																																																		(char*[]){ ".wad",																							nullptr }},
	{ WH_FILE_TYPE_PWAD,					4,  (u8[]){ 0x50, 0x57, 0x41, 0x44 },																																																																		(char*[]){ ".wad",																							nullptr }},
	{ WH_FILE_TYPE_WEBM,					4,  (u8[]){ 0x1A, 0x45, 0xDF, 0xA3 },																																																																		(char*[]){ ".mkv", ".mka", ".mks", ".mk3d", "webm",												nullptr }},
	{ WH_FILE_TYPE_WASM,					4,  (u8[]){ 0x00, 0x61, 0x73, 0x6D },																																																																		(char*[]){ ".wasm",																							nullptr }},
	{ WH_FILE_TYPE_FLV,					3,  (u8[]){ 0x46, 0x4C, 0x56 },																																																																				(char*[]){ ".flv",																							nullptr }}, // flash video
	{ WH_FILE_TYPE_TEXT_U8,				3,  (u8[]){ 0xEF, 0xBB, 0xBF },																																																																				(char*[]){ ".txt", ".text",																				nullptr }},
	{ WH_FILE_TYPE_NES,					3,  (u8[]){ 0x4E, 0x45, 0x53 },																																																																				(char*[]){ ".nes",																							nullptr }}, // nintendo entertainment system
	{ WH_FILE_TYPE_OAR,					3,  (u8[]){ 0x4F, 0x41, 0x52 },																																																																				(char*[]){ ".oar",																							nullptr }},
	{ WH_FILE_TYPE_PBM_ASCII,			3,  (u8[]){ 0x50, 0x31, 0x0A },																																																																				(char*[]){ ".pbm",																							nullptr }},
	{ WH_FILE_TYPE_PBM_BINARY,			3,  (u8[]){ 0x50, 0x34, 0x0A },																																																																				(char*[]){ ".pbm",																							nullptr }},
	{ WH_FILE_TYPE_PGM_ASCII,			3,  (u8[]){ 0x50, 0x32, 0x0A },																																																																				(char*[]){ ".pgm",																							nullptr }},
	{ WH_FILE_TYPE_PGM_BINARY,			3,  (u8[]){ 0x50, 0x35, 0x0A },																																																																				(char*[]){ ".pgm",																							nullptr }},
	{ WH_FILE_TYPE_PPM_ASCII,			3,  (u8[]){ 0x50, 0x33, 0x0A },																																																																				(char*[]){ ".ppm",																							nullptr }},
	{ WH_FILE_TYPE_PPM_BINARY,			3,  (u8[]){ 0x50, 0x36, 0x0A },																																																																				(char*[]){ ".ppm",																							nullptr }},
	{ WH_FILE_TYPE_SHELL,				2,  (u8[]){ 0x23, 0x21 }},					// shell script
	{ WH_FILE_TYPE_BMP,					2,  (u8[]){ 0x42, 0x4D },																																																																						(char*[]){ ".bmp", ".dib",																					nullptr }},
	{ WH_FILE_TYPE_EXE,					2,  (u8[]){ 0x4D, 0x5A },																																																																						(char*[]){ ".exe", ".dll",																					nullptr }},
	{ WH_FILE_TYPE_MP3,					2,  (u8[]){ 0xFF, 0xFB },																																																																						(char*[]){ ".mp3",																							nullptr }},
	{ WH_FILE_TYPE_MP3,					2,  (u8[]){ 0xFF, 0xF2 },																																																																						(char*[]){ ".mp3",																							nullptr }},
	{ WH_FILE_TYPE_MP3,					2,  (u8[]){ 0xFF, 0xF2 },																																																																						(char*[]){ ".mp3",																							nullptr }},
	{ WH_FILE_TYPE_GZIP,					2,  (u8[]){ 0x1F, 0x8B },																																																																						(char*[]){ ".gz", "tar.gz",																				nullptr }},
	{ WH_FILE_TYPE_DER,					2,  (u8[]){ 0x30, 0x82 },																																																																						(char*[]){ ".der",																							nullptr }},
	{ WH_FILE_TYPE_COM,					1,  (u8[]){ 0x09 },																																																																								(char*[]){ ".com",																							nullptr }},
};

i64 _wh_memcmp_mask(const void* c0, const void* c1, const void* mask, size_t length) {
	i64 out = 0;
	u8* cc0 = (u8*)c0;
	u8* cc1 = (u8*)c1;
	u8* m = (u8*)mask;

	if (nullptr == m) {
		wh_for(i64, i, length) {
			out += *cc0 - *cc1;

			// moving the pointer
			cc0 += 1;
			cc1 += 1;

			if (0 != out) {
				break;
			}
		}
	} else {
		wh_for(i64, i, length) {
			out += (*cc0 & *m) - (*cc1 & *m);

			// moving the pointer
			cc0 += 1;
			cc1 += 1;
			m += 1;

			if (0 != out) {
				break;
			}
		}
	}

	return out;
}

i64 _wh_file_type(const char* restrict filename, u8* restrict buffer, u64 length) {
	_wh_file_type_s* ft = nullptr;
	u64 type = WH_FILE_TYPE_UNKNOWN;
	char* extension = nullptr;

	if (nullptr != filename) {
		extension = strrchr(filename, '.');
	}

	wh_for (int, i, sizeof(formats) / sizeof(formats[0])) {
		if (formats[i].length > length) {
			continue;
		}

		if (!_wh_memcmp_mask(buffer, formats[i].signature, formats[i].mask, formats[i].length)) {
			wh_log_debug(("Found format!"));
			ft = &formats[i];
			type = formats[i].type;
			break;
		}
		
		wh_log_debug(("No match for [ %i ]"), i);
	}

	if (WH_FILE_TYPE_UNKNOWN == type) {
		if (nullptr == extension) {
			goto go_error_exit;
		}

		wh_for (int, i, sizeof(formats) / sizeof(formats[0])) {
			for (u64 j = 0; nullptr != formats[i].extensions[j]; j++) {
				// TODO check extension
				if (!strcmp(extension, formats[i].extensions[j])) {
					type = formats[i].type;
					goto go_found;
				}
			}
		}
		// use file extension
	} else if (nullptr != extension && nullptr != ft->extensions) {
		for (u64 i = 0; nullptr != ft->extensions[i]; i++) {
			// TODO check extension
			if (!strcmp(extension, ft->extensions[i])) {
				goto go_found;
			}
		}

		wh_log_warning(("Extension miss match for [ %s ]"), filename);
	}

go_found:
	return type;

go_error_exit:
	wh_log_error(("Failed to find file type!"));
	return type;
}


#ifdef __linux__
#include<unistd.h>
#include<sys/mman.h>

wh_file_s _wh_file_load(_wh_file_load_params params) {
	int fd = open(params.path, 0, 0);
	wh_file_s file = { 0 };

	if (-1 == fd) {
		wh_log_error(("Failed to find file [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.length = lseek(fd, 0, SEEK_END);

	if (0 >= file.length) {
		wh_log_error(("Failed to get length [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.ptr = mmap(nullptr, file.length, PROT_READ, MAP_SHARED, fd, 0);

	if (MAP_FAILED == file.ptr) {
		wh_log_error(("Failed to mmap file"));
		goto go_error_exit;
	}

	return file;
go_error_exit:
	return (wh_file_s){ 0 };
}

i8 _wh_file_unload(_wh_file_unload_params params) {
	if (-1 == munmap(params.file.ptr, params.file.length)) {
		wh_log_error(("munmap failed [ $n ]"), errno);
	}

	return 0;
go_error_exit:
	return -1;
}

#else
#include<windows.h>

wh_file_s _wh_file_load(_wh_file_load_params params) {
	wh_file_s file = { 0 };
	_wh_file_windows_s* windows = &file._windows;

	windows->h_fd = CreateFileA(
		params.path, GENERIC_READ, FILE_SHARE_READ, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == windows->h_fd) {
		wh_log_error(("Failed to open file [ %s ]"), params.path);
		goto go_error_exit;
	}

	file.length = GetFileSize(windows->h_fd, nullptr);

	if (INVALID_FILE_SIZE == file.length) {
		wh_log_error(("Failed to get file size [ %s ]"), params.path);
		goto go_error_exit_close_fd;
	}

	windows->h_map = CreateFileMappingA(windows->h_fd, nullptr, PAGE_READONLY, 0, 0, nullptr);

	if (nullptr == windows->h_map) {
		wh_log_error("Failed to create file mapping [ %s ]", params.path);
		goto go_error_exit_close_fd;
	}

	file.ptr = MapViewOfFile(windows->h_map, FILE_MAP_READ, 0, 0, 0);

	if (nullptr == file.ptr) {
		wh_log_error("Failed to map view of file [ %s ]", params.path);
		goto go_error_exit_close_mapping;
	}

	return file;
go_error_exit_close_mapping:
	CloseHandle(windows->h_map);
go_error_exit_close_fd:
	CloseHandle(windows->h_fd);
go_error_exit:
	return (wh_file_s) { 0 };
}

i8 _wh_file_unload(_wh_file_unload_params params) {
	_wh_file_windows_s* windows = &params.file._windows;

	if (nullptr != params.file.ptr) {
		UnmapViewOfFile(params.file.ptr);
	}

	if (nullptr != windows->h_map) {
		CloseHandle(windows->h_map);
	}

	if (INVALID_HANDLE_VALUE != windows->h_fd && nullptr != windows->h_fd)  {
		CloseHandle(windows->h_fd);
	}

	return 0;
}

#endif

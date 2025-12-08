#include<errno.h>
#include<string.h>
#include<wh-sys/filesystem.h>
#include<wh-sys/memory.h>

#include<wh/print.h>
#include<wh/debug/logger.h>

#ifndef _WIN32

#include<dirent.h>

wh_dir_s _wh_read_dir(_wh_dir_read_params params) {
	i64 error = 0;
	wh_dir_s out = {
		.count = 0,
		.entries = nullptr,
	};

	struct dirent* current = nullptr;
	DIR* dir = nullptr;

	if (nullptr == params.path) {
		error = EINVAL;
		goto go_error_exit;
	}

	if (nullptr == (dir = opendir(params.path))) {
		error = errno;
		goto go_error_exit;
	}


	for (current = readdir(dir); nullptr != current; current = readdir(dir)) {
		if (!strncmp(current->d_name, ".", NAME_MAX) || !strncmp(current->d_name, "..", NAME_MAX) ) {
			continue;
		}
		++out.count;
	}

	wh_log_debug(("Allocating [ %i ]"), out.count * sizeof(wh_dir_entry_s));
	out.entries = wh_alloc(params.heap, out.count * sizeof(wh_dir_entry_s), &out.entries, .error = &error);

	if (nullptr == out.entries) {
		wh_log_error(("Failed to allocated dir entries..."));
		goto go_error_exit_close;
	}

	rewinddir(dir);

	for (u64 length, i = 0; i < out.count;) {
		current = readdir(dir);

		if (current == nullptr) {
			wh_log_warning(("Directory count changed!"));
			out.count = i;
			break;
		}
		
		if (!strncmp(current->d_name, ".", NAME_MAX) || !strncmp(current->d_name, "..", NAME_MAX) ) {
			continue;
		}

		length = strnlen(current->d_name, NAME_MAX - 1);
		memcpy(out.entries[i].name, current->d_name, length);
		out.entries[i].name[length] = '\0';

		switch(current->d_type) {
			case DT_BLK:	out.entries[i].type = WH_FSYS_BLOCK;	break;
			case DT_CHR:	out.entries[i].type = WH_FSYS_CHAR;		break;
			case DT_DIR:	out.entries[i].type = WH_FSYS_DIR;		break;
			case DT_FIFO:	out.entries[i].type = WH_FSYS_FIFO;		break;
			case DT_LNK:	out.entries[i].type = WH_FSYS_LINK;		break;
			case DT_REG:	out.entries[i].type = WH_FSYS_FILE;		break;
			case DT_SOCK:	out.entries[i].type = WH_FSYS_SOCKET;	break;

			default:
				out.entries[i].type = WH_FSYS_UNKNOWN;
		}

		++i;
	}
		
	if (nullptr != (current = readdir(dir))) {
		wh_log_warning(("Directory resized mid read!"));
		error = ERANGE;
	}

go_error_exit_close:
	closedir(dir);
go_error_exit:
	if (nullptr != params.error) {
		*params.error = error;
	}
	return out;
}


void wh_dir_destroy(wh_heap_header_s* heap, wh_dir_s* dir) {
	wh_free(heap, dir->entries, &dir->entries);
}

#else

wh_dir_s _wh_read_dir(_wh_dir_read_params params) {
	return (wh_dir_s) { 0 };
}

void wh_dir_destroy(wh_heap_header_s* heap, wh_dir_s* dir) {
}

#endif

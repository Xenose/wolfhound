#include<dirent.h>
#include<string.h>
#include<wh/sys/filesystem.h>
#include<wh/memory.h>

#include<wh/print.h>
#include<wh/debug.h>

wh_dir_s wh_read_dir(wh_heap_header_s* heap, const char* path) {
	wh_dir_s out = {
		.count = 0,
		.entries = nullptr,
	};

	struct dirent* current = nullptr;
	DIR* dir = nullptr;

	if (nullptr == (dir = opendir(path))) {
		goto go_error_exit;
	}

	for (current = readdir(dir); nullptr != current; current = readdir(dir)) {
		if (strcmp(current->d_name, ".") == 0 || strcmp(current->d_name, "..") == 0) {
			continue;
		}
		++out.count;
	}

	out.entries = wh_mem_alloc(heap, out.count * sizeof(wh_dir_entry_s), &out.entries);

	if (nullptr == out.entries) {
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
		
		if (strcmp(current->d_name, ".") == 0 || strcmp(current->d_name, "..") == 0) {
			continue;
		}

		length = strnlen(current->d_name, NAME_MAX - 1);
		memcpy(out.entries[i].name, current->d_name, length);
		out.entries[i].name[length] = '\0';

		wh_print(("File is named [ %s ]\n"), out.entries[i].name);

		switch(current->d_type) {
			case DT_BLK:
			case DT_CHR:
			case DT_DIR:
			case DT_FIFO:
			case DT_LNK:
			case DT_REG:
			case DT_SOCK:
			default:
				out.entries[i].type = 0;
		}

		++i;
	}
		
	if (nullptr != (current = readdir(dir))) {
		wh_log_warning(("Directory resized mid read!"));
	}

go_error_exit_close:
	closedir(dir);
go_error_exit:
	return out;
}


void wh_dir_destroy(wh_heap_header_s* heap, wh_dir_s* dir) {
	wh_mem_free(heap, dir->entries, &dir->entries);
}

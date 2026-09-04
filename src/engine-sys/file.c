#include<wh-posix/errno.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/string.h>
#include<wh-posix/sys/mman.h>
#include<wh-posix/unistd.h>
#include<wh-sys/file.h>
#include<wh-sys/debug/logger.h>
#include<wh/memory/core.h>

// Splitting the giant array into its own C file...
#include"_file_extensions.c"

i64 _wh_file_type(const char* restrict filename, u8* restrict buffer, u64 length) {
    _wh_file_type_s* ft = nullptr;
    i64 type = WH_FILE_TYPE_UNKNOWN;
    char* extension = nullptr;

    if (nullptr != filename) {
        extension = strrchr(filename, '.');
    }

    wh_for (i64, i, (i64)(sizeof(formats) / sizeof(formats[0]))) {
        if (formats[i].length > length) {
            continue;
        }

        if (!wh_memcmp_mask(buffer, formats[i].signature, formats[i].length, formats[i].mask)) {
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

        wh_for (i64, i, (i64)(sizeof(formats) / sizeof(formats[0]))) {
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

    file.ptr = mmap(nullptr, (size_t)file.length, PROT_READ, MAP_SHARED, fd, 0);

    if (MAP_FAILED == file.ptr) {
        wh_log_error(("Failed to mmap file"));
        goto go_error_exit;
    }

    return file;
go_error_exit:
    return (wh_file_s){ 0 };
}

i8 _wh_file_unload(_wh_file_unload_params params) {
    if (-1 == munmap(params.file.ptr, (size_t)params.file.length)) {
        wh_log_error(("munmap failed [ $n ]"), errno);
    }

    return 0;
go_error_exit:
    return -1;
}

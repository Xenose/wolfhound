#include<wh/debug/exceptions.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-posix/errno.h>
#include<wh-posix/dirent.h>
#include<wh-posix/dlfcn.h>

#include<wh-sys/info.h>

#include<wh-testing/unit.h>

#include<wh/string.h>

#define PATH_LENGTH 1024

void str_append(char* buffer, int buffer_size, char* str) {
    int len = strlen(buffer);

    if (0 > (buffer_size - len)) {
        // TODO error
    }

    strncpy(&buffer[len], str, strlen(str));
}

void* add_test(wh_unit_results_s* results, void** out, const char* name, const char* path) {
    wh_unit_test_s* ptr = nullptr;
    void* handle = dlopen(path, RTLD_NOW);
    
    if (nullptr == handle) {
        printf("Failed to load test [ %s ] -> %s\n", path, dlerror());
        goto go_error_exit;
    }

    dlerror();
    ptr = realloc(results->ptr, sizeof(wh_unit_test_s) * (results->count + 1));

    if (nullptr == ptr) {
        goto go_error_exit;
    }

    results->ptr = ptr;
    ptr[results->count].name = strdup(name);

    *out = &ptr[results->count];
    ++results->count;
    return handle;

go_error_exit_dlclose:
    dlclose(handle);
go_error_exit:
    return nullptr;
}

int main(int arc, char* const* arv) {
    wh_unit_results_s results = { 0 };

    char path[PATH_LENGTH] = { 0 };
    int path_length = PATH_LENGTH - 1;
    int path_end = 0;

    DIR* dir = nullptr;
   
    // Constructing the test path and getting the
    // end of the path.
    wh_sys_program_path(path, path_length);
    str_append(path, path_length, "tests/");
    path_end = strlen(path);

    printf("Path is [ %s ]\n", path);

    if (nullptr == (dir = opendir(path))) {
        printf("Failed to open path!\n");
        goto go_error_exit;
    }

    printf("\n\n");

    for (struct dirent* entry = readdir(dir); nullptr != entry; entry = readdir(dir)) {
        void* ptr = nullptr;

        if ('_' == entry->d_name[0] || 0 == strcmp(entry->d_name, ".") || 0 == strcmp(entry->d_name, "..")) {
            continue;
        }

        str_append(path, path_length, entry->d_name);
        printf("Executing test [ %s ]\n", path);

        void* handle = add_test(&results, &ptr, entry->d_name, path);
        
        if (nullptr == handle) {
            goto go_memset;
        }

        wh_try {
            i64 (*test)(wh_unit_test_s* info) = dlsym(handle, "init");
            test(ptr);
        } wh_catch(wh_exception_s, _ex) {
            printf("Test failed!\n");
            goto go_dlclose; // TODO fix as its continue without stopping.
        }

go_dlclose:
        dlclose(handle);
go_memset:
        // Resetting the path so we can reuse it for the next test.
        memset(&path[path_end], 0, path_length - path_end);
    }

    closedir(dir);
    //test_strings(&results);
    return 0;
go_error_exit:
    return -1;
}

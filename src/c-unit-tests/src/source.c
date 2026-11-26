#include<wh/debug/exceptions.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/string.h>
#include<wh-posix/errno.h>
#include<wh-posix/dirent.h>
#include<wh-posix/dlfcn.h>
#include<wh-posix/getopt.h>

#include<wh-testing/unit.h>
#include<wh-sys/info.h>
#include<wh/string.h>
#include<wh/debug/signalar.h>

#define PATH_LENGTH 1024

typedef struct {
    struct {
        size_t count;
        char** names;
    } filter;

    struct {
        int end;                    // same as length but should change for allowing path resets.
        int length;
        char array[PATH_LENGTH];
    } path;
} test_settings_s;

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

i64 report(wh_unit_results_s* results) {
    wh_for(i64, i, results->count) {
        wh_unit_test_s* r = &results->ptr[i];

        printf(
            "\nREPORT [ %s : TEST %li of %li ]\n"
            "\tPassed tested    : %li of %li"
            "\nERRORS\n"
            "\tExit status      : %s\n"
            "\tLast function    : %s\n"
            "\tLast line called : %lu\n"
            "\n",
            r->name, i + 1, results->count,
            r->passed, r->passed + r->failed,
            r->error.msg, // Can cause issues needs more testing
            r->error.last_function,
            r->error.last_line
        );
    }

    return 0;
}

char** args_filter_tests(size_t* count, const char* string) {
    char** out = nullptr;

    i64 index = 0;
    int status = 0;
    ssize_t length = 0;

    (*count) = 0;

    // Testing items before the final item.
    do {
        char** p = nullptr;
        status = wh_string_split(&length, &index, string, ",");

        if (0 == length) {
            break;
        }
        
        p = realloc(out, (*count + 1) * sizeof(char*));

        if (nullptr == p) {
            break;
        }
        
        out = p;

        // Copying the new string to the memory location.
        out[*count] = strndup(&string[index], length);
        ++(*count);
    } while(-1 != status);

    return out;
}

void parse_options(int arc, char* const* arv, test_settings_s* settings) {
    int opt = 0;

    while (-1 != (opt = getopt(arc, arv, "t:"))) {
        switch(opt) {
            case 't':
                settings->filter.names = args_filter_tests(&settings->filter.count, optarg);
                break;
            default:
                break;
        }
    }
}

void setup_basepath(test_settings_s* settings) {
    // Constructing the test path and getting the
    // end of the path.
    wh_sys_program_path(settings->path.array, settings->path.length);
    str_append(settings->path.array, settings->path.length, "tests/");
    settings->path.end = strlen(settings->path.array);

    printf("Path is [ %s ]\n", settings->path.array);
}

void run_tests(DIR* dir, wh_unit_results_s* results, test_settings_s* settings) {
    for (struct dirent* entry = readdir(dir); nullptr != entry; entry = readdir(dir)) {
        wh_unit_test_s* ptr = nullptr;

        if ('_' == entry->d_name[0] || 0 == strcmp(entry->d_name, ".") || 0 == strcmp(entry->d_name, "..")) {
            continue;
        }

        // We don't need to check null as count will be zero
        // if names is nullptr.
        if (0 != settings->filter.count) {
            for (int i = 0; i < settings->filter.count; i++) {
                if (!strcmp(settings->filter.names[i], entry->d_name)) {
                    goto go_found_match;
                }
            }

            // didn't find a match skipping entry.
            continue;
        }

go_found_match:
        str_append(settings->path.array, settings->path.length, entry->d_name);
        printf("Executing test [ %s ]\n", settings->path.array);

        void* handle = add_test(results, (void*)&ptr, entry->d_name, settings->path.array);

        if (nullptr == handle) {
            goto go_memset;
        }

        wh_try {
            i64 (*test)(wh_unit_test_s* info) = dlsym(handle, "init");

            if (NULL != test) {
                test(ptr);
            }

            ptr->error.msg = nullptr;
        } wh_catch(wh_exception_s, ex) {
            ptr->error.msg = ex.msg;
        }

        wh_try {
            i64 (*destructor)(wh_unit_test_s* info) = dlsym(handle, "destructor");

            if (NULL == destructor) {
                // TODO handle error
                // printf("\t[ \033[31mDLSYM\033[0m ] Destructor failed!\n");
            } else {
                destructor(ptr);
            }

        } wh_catch(wh_exception_s, ex) {
        }

go_dlclose:
        // Check for valid handle...
        //dlclose(handle);
go_memset:
        // Resetting the path so we can reuse it for the next test.
        memset(&settings->path.array[settings->path.end], 0, settings->path.length - settings->path.end);
    }
}

int main(int arc, char* const* arv) {
    wh_unit_results_s results = { 0 };
    DIR* dir = nullptr;

    test_settings_s settings = {
        .path = {
            .length = PATH_LENGTH - 1,
        },
    };

    // Adding the signalar backtrace.
    wh_signalar_init(arv[0]);
    setup_basepath(&settings);
    parse_options(arc, arv, &settings);

    if (nullptr == (dir = opendir(settings.path.array))) {
        printf("Failed to open path!\n");
        goto go_error_exit;
    }

    run_tests(dir, &results, &settings);
    closedir(dir);
    //test_strings(&results);
    return report(&results);
go_error_exit:
    return -1;
}

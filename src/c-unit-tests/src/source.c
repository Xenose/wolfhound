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

WH_TEST_FUNC(test_strings) {
    WH_TEST(wh_strcat) {
        int64_t error = 0;
        char buffer[256] = { 0 };

        // Easy test for wh_strcat
        error = 0;
        wh_strcat((buffer, 255), "Hello,", " ", "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, world!", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, 0l, error);
      
        error = 0;
        memset(buffer, 0, 256);
        wh_strcat((buffer, 255), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, world!", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, 0l, error);

        error = 0;
        memset(buffer, 0, 256);
        wh_strcat((buffer, 10, .error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "Hello, wor", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)ENOMEM, error);
        
        error = 0;
        memset(buffer, 0, 256);
        wh_strcat((.buffer_length = 10, .error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)EFAULT, error);

        error = 0;
        memset(buffer, 0, 256);
        wh_strcat((.error = &error), "Hello,", " ", nullptr, "world!");
        WH_TEST_STREQ(wh_strcat, "", buffer, "wh_strcat::world_test");
        WH_TEST_INT64EQ(wh_strcat, (int64_t)ENOBUFS, error);
        WH_TEST_INT64EQ(wh_strcat, (int64_t)ENOBUFS, error + 1);
    }
}

void str_append(char* buffer, int buffer_size, char* str) {
    int len = strlen(buffer);

    if (0 > (buffer_size - len)) {
        // TODO error
    }

    strncpy(&buffer[len], str, strlen(str));
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
        str_append(path, path_length, entry->d_name);
        printf("Executing test [ %s ]\n", path);

        void* handle = dlopen(path, 0);

        if (nullptr == handle) {
            printf("Failed to load test [ %s ] -> %s\n", path, dlerror());
            continue;
        }

        dlerror();

        // Resetting the path so we can reuse it for the next test.
        memset(&path[path_end], 0, path_length - path_end);
    }

    closedir(dir);
    //test_strings(&results);
    return 0;
go_error_exit:
    return -1;
}

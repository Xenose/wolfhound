#include<wh-posix/stdio.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/unistd.h>
#include<wh-posix/libproc.h>

#include<wh-core/data/array.h>
#include<wh-core/data/hashmap.h>

static size_t _hash(const u8* ptr, void* array) {
    return 0;
}

WH_DARRAY(int, test_array) test_array_struct;
WH_HASHMAP(int, test_hashmap, &_hash) test_hashmap_struct;

static void* _resize(void* ptr, int count, int type_size) {
    test_array_struct* array = ptr;
    size_t c = 0;
    void* p = nullptr;

    printf("%p\n", array);

    c = (array->size + count) * type_size;
    p = realloc(array->array, c);

    if (nullptr == p) {
        printf("Failed to reallocate array!\n");
    } else {
        printf("Reallocated array!\n");
        array->array = p;
        array->size = c / type_size;
    }

    return array->array;
}

static void* _resize_hash(void* ptr, int count, int type_size) {
    return nullptr;
}

int main(int arc, char* const* arv) {
   int nb = 0;
   char message[] = "Hello, world!\n";

   nb = write(1, message, sizeof(message) / sizeof(message[0]));

   int fd = open("README.md", O_RDONLY, 0);

   printf("Read fd [ %i ]\n", fd);

   if (0 == close(fd)) {
      printf("Closed socket!\n");
   }

   proc_status_t pstatus = { 0 };

   proc_read(getpid(), &pstatus); 
   proc_print(&pstatus);

   WH_DARRAY_RESIZE(&test_array, 10, _resize); 

   printf("--> %i\n", WH_DARRAY_VALUE(&test_array, 9));
   WH_DARRAY_VALUE(&test_array, 9) = 10;
   printf("--> %i\n", WH_DARRAY_VALUE(&test_array, 9));
   WH_DARRAY_CLEAR(&test_array, 9);
   printf("--> %i\n", WH_DARRAY_VALUE(&test_array, 9));
   printf("--> %lu\n", WH_DARRAY_SIZE(&test_array));

   WH_HASHMAP_RESIZE(&test_hashmap, 10, _resize_hash);
   return 0;
}

#include<wh-posix/stdio.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/unistd.h>
#include<wh-posix/libproc.h>

#include<wh-core/data/array.h>

WH_DARRAY(int, test_array);

static void* _resize(void* ptr, int size, int type_size) {
    void* p = realloc(ptr, size * type_size);

    if (nullptr == p) {
        printf("Failed to reallocate array!\n");
    } else {
        printf("Reallocated array!");
        ptr = p;
    }

    return ptr;
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

   WH_DARRAY_RESIZE(&test_array, 100, _resize); 
   

   return 0;
}

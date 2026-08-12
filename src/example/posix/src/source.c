#include<wh-posix/stdio.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/stdlib.h>
#include<wh-posix/unistd.h>
#include<wh-posix/libproc.h>

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

   return 0;
}

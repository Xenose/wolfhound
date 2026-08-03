#include<stdio.h>
#include<wh-posix/fcntl.h>
#include<wh-posix/stdlib.h>

int main(int arc, char* const* arv) {
   int nb = 0;
   char message[] = "Hello, world!\n";

   nb = write(1, message, sizeof(message) / sizeof(message[0]));

   int fd = open("README.md", O_RDONLY, 0);

   printf("Read fd [ %i ]\n", fd);

   return 0;
}
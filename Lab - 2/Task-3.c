#include <sys/types.h> // Type definitions used by many programs
#include <stdio.h> // Standard I/O functions
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>

int main(int argc, char *argv[])
{
   int a = 0, b = 1, n = a+b, i, size;
   pid_t pid;

   printf("Enter the number of the Fibonacci Sequence: \n");
   scanf("%d", &size);

   if(size > 0)
   {
    pid = fork();
      if (pid > 0)
      {
         printf("Parent Process started.\n");
         wait(NULL);
         printf("Parent Process ended.\n");
      }
      else
      {
         printf("Child Process started.\n");
         printf("%d %d", a, b);
         for (i = 2; i < size; i++)
         {
            n = a + b;
            printf(" %d", n);
            a = b;
            b = n;
         }

         printf("\nChild Process ended.\n");
      }
   }

   return 0;
}
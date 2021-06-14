#include <sys/types.h> // Type definitions used by many programs
#include <stdio.h> // Standard I/O functions
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int value = 0;
    int pid1, pid2;

    pid1 = fork();
    
    if(pid1==0){ // Checks if child process
        value = value + 180042110;
        printf("Value From Child Process: %d\n",value);
        exit(0);
    }
    
    else{ // Checks if parent process
        value = value + 110;
        printf("Value From Parent Process: %d\n",value);
        exit(0);
    }

}
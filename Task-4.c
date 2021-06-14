#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include <sys/wait.h>

int main()
{
    pid_t pid1;
    int array[100];
    int fd[2];

    if(pipe(fd) == -1) 
        return 2;

    int numToSearch = 0, arraySize, temp;

    printf("\nSize of Array: ");
    scanf("%d", &arraySize);

    printf("\nNon-Negative Integers:\n");
    for(int i=0; i<arraySize; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("\nEnter the value to search: ");
    scanf("%d", &numToSearch);

    while(numToSearch < 0)
    {
        printf("\nEnter a non-negative integer.");
        printf("\nEnter the value to search: ");
        scanf("%d", &numToSearch);
    }

    pid1 = fork();
    if(pid1 < 0)
        printf("\nForking failed\n");
    else if(pid1 == 0)
    {
        close(fd[0]);

        printf("\nChild Process started.\n");

        // Bubble Sort
        for (int j = 0; j < arraySize-1; j++)
        {
            for (int k = 0; k < arraySize-j-1; k++)
            {
                if (array[k] > array[k+1])
                {
                    temp = array[k];
                    array[k] = array[k+1];
                    array[k+1] = temp;
                }
            }
        }

        printf("Sorted Array:\n");
        for (int j = 0; j < arraySize; j++)
        {
            printf("%d ", array[j]);
        }
        printf("\nChild Process ends.\n");

        if(write(fd[1], array, sizeof(int)*arraySize) < 0 ){
            return 3; // Throw error 3
        }

        close(fd[1]);
    }
    else
    {
        printf("\nParent Process has started and is waiting for the Child Process to finish\n");
        wait(NULL);

        printf("\nParent Process has started again.");
        printf("\nParent Process is searching for the number: %d", numToSearch);

        close(fd[1]);

        int array[arraySize];
        if(read(fd[0], array, sizeof(int)*arraySize) <0)
        {
            return 6; //Throw error 6
        }

        close(fd[0]);

        // Binary Search

        int first = 0;
        int last = arraySize - 1;
        int middle;
        while (first <= last)
        {
            middle = (first + last)/2;
            if (array[middle] == numToSearch){
                printf("\n%d is found!\n", numToSearch);
                break;
            }

            else if (array[middle] < numToSearch )
            {
                first = middle + 1;
            }
            else{
                last = middle - 1;
            }

        }

        if (first > last)
            printf("\nNot found. %d is not present in the array.\n", numToSearch);

        printf("Parent Process ends here.\n");
    }

    return 0;
}

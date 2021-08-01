#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmid = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);

    int *str = (int*) shmat(shmid,NULL,0);

    int search = -1, array[100], arrSize, temp;

    printf("Size of Array:\n");
    scanf("%d", &arrSize);

    printf("Non-Negative Integers: ");
    for(int i=0; i<arrSize; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Checking for Non-Negative Integers\n");
    for(int i=0; i<arrSize; i++)
    {
        printf("%d ", array[i]);
        if(array[i]<0)
        {       
            printf("\n");
             printf("Invalid input in the array. Program terminates here.\n");
            return 0;
        }
    }

    while(search < 0)
    {
        printf("\nValue to search: ");
        scanf("%d", &search);
    }

    printf("\n");

    pid_t p = fork();

    if (p < 0)
    {
        printf("Forking Failed" );
        return 1;
    }

    // Parent starts here
    else if (p > 0)
    {
        wait(NULL);
        int i;
        int first = 0;
        int last = arrSize - 1;
        int middle = (first + last)/2;

        while (first <= last)
        {
            if (str[middle] < search)
                first = middle + 1;
            else if (str[middle] == search)
            {
                printf("\n%d is present in the array.\n", search);
                break;
            }
            else
                last = middle - 1;

            middle = (first + last)/2;
        }

        if (first > last)
            printf("\n %d is not present in the array.\n", search);

        printf("Parent Process ends here.\n");

        shmdt(str);
    }

    // Child starts here
    else
    {

        int i;

        printf("Data written in shared memory: \n");

        for (int j = 0; j < arrSize-1; j++)
        {
            for (int k = 0; k < arrSize-j-1; k++)
            {
                if (array[k] > array[k+1])
                {
                    temp = array[k];
                    array[k] = array[k+1];
                    array[k+1] = temp;
                }
            }
        }
        printf("Sorted Array by Child Process:\n");
        for (int j = 0; j < arrSize; j++)
        {
            printf("%d ", array[j]);
            str[j]=array[j];
        }

        printf("\n");
        shmdt(str);

        shmctl(shmid,IPC_RMID,NULL); // Terminating the shared memory

        printf("Child Process ends here.\n");
        exit(0);
    }

    return 0;
}

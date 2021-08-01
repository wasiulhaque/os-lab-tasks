#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int fib_arr[1000];


void* func(void* arg)
{
    int num,x=0,i;
    int first=1, second=1;


    printf("Inside the thread now.\n");

    num = *(int*)arg;

    if(num==0)
    {
        fib_arr[num]=first;
    }
    else if(num==1)
    {
        fib_arr[num]=second;
    }
    else
    {
        fib_arr[num]=fib_arr[num-1]+fib_arr[num-2];
    }
   // exit the current thread
    pthread_exit(NULL);
}



int main()
{
    int i,number;
    printf("Enter the number : \n");
    scanf("%d",&number);

    pthread_t ptid[number];

    printf("Fibonacci sequence :\n");
    // Creating a new thread
    //MODIFICATION : for printing the output in parent thread as soon as
    // they are generated in child thread,we need to create separate thread
    //for calculating each number and print that number in the parent thread.
    for(i=0; i<number; i++)
    {
        pthread_create(&ptid[i], NULL, func, &i);
        pthread_join(ptid[i],NULL);
        printf("%d \t\n",fib_arr[i]);
    }

    printf("\n");
    printf("Thread ends\n");

    pthread_exit(NULL);

    return 0;
}


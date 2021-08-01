#include <sys/types.h> // Type definitions used by many programs 
#include <stdio.h> // Standard I/O functions 
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants 
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>
#include <pthread.h>

void* generateFibonacciSeries (void *NumOfTerms)
{
    // detach the current thread from the calling thread
    // pthread_detach(pthread_self());

    int arr[1000];
    int N = *((int*)NumOfTerms);

    int a = 0, b = 1, nextTerm = a+b;

    printf("\nInside the thread now..\n");
    printf("Child thread generating the fibonacci series here.");

    int index = 2;
            
    arr[0] = a;
    arr[1] = b; 
            
    for (int i = 0; i < N - 1; i++){
        nextTerm = a + b;
        arr[index] = nextTerm;
                
        a = b;
        b = nextTerm;
                
        index++ ;
    }

    // exit the current thread
    pthread_exit(arr);
}

void create_Thread()
{
    printf("Entering the Child Thread here.\n");

    int N;
    void *result_array;

    startOfTheSeries:
        printf("Number of Fibonacci Series: ");
        scanf("%d", &N);

    if ( N <= 0 ){
        printf("Error. A non-negative integer is required.\n");
        goto startOfTheSeries;
    }

    // Creating a new thread
    pthread_t ptid;
    pthread_create( &ptid, NULL, generateFibonacciSeries, &N );

    // Waiting for the created thread to terminate
    printf("\nThe Parent Thread is waiting here.\n");
    pthread_join( ptid, &result_array );

    printf("\nThe Child thread has ended.\n");
    
    printf("\nThe Parent thread printing the Fibonacci Series here.\n");

    printf("Fibonacci Series: ");
    for (int j = 0; j < N; j++)
        printf("%d ", ((int*)result_array)[j]);

    printf("\nParent Thread ends.\n");
    pthread_exit(NULL);
    
}

// Driver code
int main()
{
    create_Thread();
    return 0;
}
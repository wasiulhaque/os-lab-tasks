#include <sys/types.h> // Type definitions used by many programs 
#include <stdio.h> // Standard I/O functions 
#include <stdlib.h> // Prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constants 
#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions
#include <sys/wait.h>
#include <pthread.h>

// Maximum Size of Matrix
#define MAX 5

int matA[MAX][MAX], matB[MAX][MAX], matC[MAX][MAX];
int n_A, m_A_B, n_B;
//int Thread_Num = 0;

struct positions {
    int i;
    int j;
};

void *Multiply (void* Position)
{
    struct positions* pos = (struct positions*) Position;

    int i = pos->i;
    int j = pos->j;

    free(pos);

    //Thread_Num++;
    //printf("\nCalculating inside Thread No: %d\n", Thread_Num);

    //printf("\nValue of i: %d, Value of j: %d\n\n", i, j);
    matC[i][j] = 0;

    for (int n = 0; n < m_A_B; n++)
    {
        matC[i][j] = matC[i][j] + (matA[i][n] * matB[n][j]);
    }
    
    //printf("\nMatC[i][j]: %d\n\n", matC[i][j]);

    // Exit the current thread
    pthread_exit(NULL);
}

void create_Thread()
{
    printf("Entering the separate child thread here.\n");

    printf("\nNumber of rows for Matrix A: ");
    scanf("%d", &n_A);

    printf("\nNumber of columns for Matrix A and rows for Matrix B: ");
    scanf("%d", &m_A_B);

    printf("\Number of columns for Matrix B: ");
    scanf("%d", &n_B);

    if ( n_A <= 0 || m_A_B <= 0 || n_B <= 0 ){
        printf("Error. Please enter a non-negative integer.\n");
        printf("The Process is terminated.\n");
    }

    else if ( n_A > 5 || m_A_B > 5 || n_B > 5 ){
        printf("Error. Dimension of Matrix has exceeded.\n");
        printf("The Process is terminated.\n");
    }

    else{
        // Matrix A
        printf("Input Matrix A :\n");
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < m_A_B; j++) {
                scanf("%d", &matA[i][j]);
            }
        }

        // Matrix B
        printf("Input Matrix B :\n");
        for (int i = 0; i < m_A_B; i++) {
            for (int j = 0; j < n_B; j++) {
                scanf("%d", &matB[i][j]);
            }
        }

        // Creating a new thread
        pthread_t ptid[n_A*n_B];
        
        int index = 0;
        for (int i = 0; i < n_A; i++){
            for (int j = 0; j < n_B; j++){
                struct positions *pos = malloc(sizeof(struct positions));
                pos->i = i;
                pos->j = j;

                pthread_create( &ptid[index], NULL, Multiply, pos );
                index++;
            }
        }

        // Waiting for the created thread to terminate
        index = 0;
        for (int i = 0; i < n_A; i++){
            for (int j = 0; j < n_B; j++){
                pthread_join( ptid[index], NULL );
                index++;
            }
        }

        printf("\nThe threads have successfully completed calculation.\n");

        printf("\nProduct of Matrix A and B, Matrix C :\n");
        for (int i = 0; i < n_A; i++){
            for (int j = 0; j < n_B; j++){
                printf("%d ", matC[i][j]);
            }
            printf("\n");
        }
        
        pthread_exit(NULL);
    }
}

// Driver code
int main()
{
    create_Thread();
    return 0;
}
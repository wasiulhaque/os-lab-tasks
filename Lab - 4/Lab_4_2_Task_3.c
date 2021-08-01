#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

void *customer(void *num);
void *barber(void *);
sem_t waitingRoom;
sem_t barberChair;
sem_t sleeingBarber;
sem_t waitingCustomer;

int allDone = 0;

int main(int argc, char *argv[])
{
    pthread_t btid;
    pthread_t tid[100];
    long RandSeed;
    int i, nCustomers, nChairs;
    int arr[100];

    printf("Enter the number of Customers : ");
    scanf("%d",&nCustomers) ;
    printf("Enter the number of Charis : ");
    scanf("%d",&nChairs);

    if (nCustomers > 100)
    {
        printf("The maximum number of customers allowed is 100.\n");
        exit(-1);
    }

    for (i=0; i<100; i++)
    {
        arr[i] = i;
    }

    sem_init(&waitingRoom, 0, nChairs);
    sem_init(&barberChair, 0, 1);
    sem_init(&sleeingBarber, 0, 0);
    sem_init(&waitingCustomer, 0, 0);

    pthread_create(&btid, NULL, barber, NULL);

    for (i=0; i<nCustomers; i++)
    {
        pthread_create(&tid[i], NULL, customer, (void *)&arr[i]);
        sleep(1);
    }

    for (i=0; i<nCustomers; i++)
    {
        pthread_join(tid[i],NULL);
        sleep(1);
    }

    sem_post(&sleeingBarber);
    pthread_join(btid,NULL);
}

void *customer(void *number)
{
    int num = *(int *)number;

    sem_wait(&waitingRoom);
    printf("Customer %d is waiting.\n", num);

    sem_wait(&barberChair);

    sem_post(&waitingRoom);

    printf("Customer %d waking up the barber.\n", num);
    sem_post(&sleeingBarber);

    sem_wait(&waitingCustomer);

    sem_post(&barberChair);

}

void *barber(void *junk)
{
    while (!allDone)
    {
        if(!allDone)
        {
            printf("The barber is sleeping.\n");
            sem_wait(&sleeingBarber);
            printf("The barber has finished his work.\n");
            sem_post(&waitingCustomer);
        }
        else
        {
            exit(0);
        }
    }
}


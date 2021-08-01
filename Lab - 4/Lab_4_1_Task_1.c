#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * func(void * num){
    pthread_detach(pthread_self());

    int i,j;

    int* n1 = (int*) num;

    int n = *n1;

    printf("Value recieved in the Thread: %d\n",n);

    printf("The Prime Numbers are: \n");    
    for(i=2;i<=n;i++)
    {
        int c=0;
        for(j=1;j<=i;j++)
        {
            if(i%j==0)
            {
                c++;
            }
        }
         
       if(c==2)
        {
            printf("%d\n ",i);
        }
    }
    pthread_exit(NULL);

}

void fun(){
    int n;
    printf("Enter the number\n");
    scanf("%d", &n);

    void *ptr = &n;

   

    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, ptr);

    pthread_join(ptid, NULL);

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

int main(){
    fun();
    return 0;
}
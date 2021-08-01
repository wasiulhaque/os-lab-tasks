#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    int fd1[2];

    pid_t p;

    int n;

    printf("Number of Terms: ");
    scanf("%d", &n);

    if(pipe(fd1)==-1)
    {
        printf("Pipe Failed");
        return 1;
    }

    p = fork();

    if(p<0)
    {
        printf("Forking Failed");
        return 1;
    }

    //Parent starts here
    else if(p > 0)
    {
        wait(NULL);
        printf("\nParent Process ID %d\n",getpid());

        close(fd1[1]); 

        int i,output_int[n];

        read(fd1[0], output_int, sizeof(output_int));

        printf("Data from the Pipe: \n");
        for(i=0;i<sizeof(output_int);i++)
        {
            if(i<n){
            printf("%d ",output_int[i]);
            printf("\n");
            }
        }

        printf("Parent Process ends here.\n");
        return 1;
    }
    
    //child starts here
    else
    {
        printf("Child Process ID %d\n",getpid());

        int i, array[n];
        int t1 = 0, t2 = 1;
        int nextTerm = t1 + t2;

        for (i = 0; i <= n; ++i) {
            if(i==0){
                array[i]=t1;
            }
            else if(i==1){
                array[i]=t2;
            }
            else{
                array[i] = nextTerm;
                t1 = t2;
                t2 = nextTerm;
                nextTerm = t1 + t2;
            }
        }

        close(fd1[0]);

        write(fd1[1], array, sizeof(array));
        printf("\nData written in pipe\n");
        close(fd1[1]);

        printf("Child Process ends here.\n");
        return 1;
    }

    return 0;
}

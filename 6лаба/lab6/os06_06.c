#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mx;

void *threadA(void *arg)
{
    for (int i = 0; i < 90; i++)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mx);
        }

        printf("child A: %d\n", i);

        if (i == 60)
        {
            pthread_mutex_unlock(&mx);
        }

        usleep(100000);

    }
    pthread_exit("Child Thread");
}

void *threadB(void *arg)
{
    for (int i = 0; i < 90; i++)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mx);
        }

        printf("child B: %d\n", i);

        if (i == 60)
        {
            pthread_mutex_unlock(&mx);
        }

        usleep(100000);

    }
    pthread_exit("Child Thread");
}

int main()
{
    pthread_mutex_init(&mx, NULL);
    pthread_t thA, thB;
    void *rA, *rB;
    pid_t pid = getpid();
    printf("main: pId = %d \n", getpid());

    int resA = pthread_create(&thA, NULL, threadA, NULL);
    int resB = pthread_create(&thB, NULL, threadB, NULL);

    for (int i = 0; i < 90; i++)
    {
        if (i == 30)
        {
            pthread_mutex_lock(&mx);
        }

        printf("main: %d \n", i);

        if (i == 60)
        {
            pthread_mutex_unlock(&mx);
        }
        
        usleep(100000);

    }

    int status1 = pthread_join(thA, (void **)&rA);
    int status2 = pthread_join(thB, (void **)&rB);

    pthread_mutex_destroy(&mx);
    exit(0);
}

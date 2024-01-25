#define GNU_SOURSE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
// ps -eLf
//gcc -D_REENTRANT -std=c99 os04_07.c -o os04_07 -lpthread

void *thread1(void *arg)
{
    pid_t pid = getpid();
    pid_t tid = pthread_self();
    int xtid = syscall(SYS_gettid);
    for (int i = 0; i < 75; i++)
    {
        sleep(1);
        printf("OS04_07_T1:PID: %d-#%d \ttid: %d \txtid: %d  \n", pid, i, tid, xtid);
    }
    pthread_exit("Child thread");  

}

int main()
{
    pthread_t a_thread; //идентификатор созданного потока
    void *thread_result;
    pid_t pid = getpid();
    pid_t tid = pthread_self();
    int xtid = syscall(SYS_gettid);
    int res = pthread_create(&a_thread, NULL, thread1, NULL);

    for (int i = 0; i < 100; i++)
    {
        
        sleep(1);
        printf("OS04_07: PID:\t%d-#%d \ttid: %d \txtid: %d  \n", pid, i, tid, xtid);
    }

    int status = pthread_join(a_thread, (void **)&thread_result);
    exit(0);
}

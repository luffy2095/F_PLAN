#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define N 5

void *worker_thread(void *arg)
{
        printf("This is worker_thread #%ld\n", (long)arg);
        usleep(400);
        pthread_exit(NULL);
}

int main()
{
        pthread_t my_thread[N];

        long id;
        for(id = 1; id <= N; id++) {
                int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
                pthread_join(my_thread[id],NULL);
                if(ret != 0) {
                        printf("Error: pthread_create() failed\n");
                        exit(EXIT_FAILURE);
                }
        }
        printf("parent exit\n");

        pthread_exit(NULL);
}

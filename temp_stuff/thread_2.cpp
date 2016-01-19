#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* deposit(void *arg);
void* withdraw(void *arg );
int balance = 1000;
pthread_t t1,t2;
int main()
{
long id;

pthread_create(&t1, NULL, deposit, (void*)1);
usleep(1);
pthread_create(&t2, NULL, withdraw, (void*)2);
pthread_join(t1, NULL);
printf("all done: balance = %d\n", balance);
pthread_exit(NULL);
}
void* deposit(void *arg)
{
int i;
pthread_t t2;
for(i=0; i<2000; ++i)
{++ balance;}
pthread_exit(NULL);
}

void* withdraw(void *arg)
{
pthread_join(t1,NULL);
int i;
for(i=0; i<100; ++i)
-- balance;
pthread_exit(NULL);
}

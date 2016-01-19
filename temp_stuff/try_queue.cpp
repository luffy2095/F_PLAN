#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<queue>
#include<time.h>
#include <inttypes.h>
#include <math.h>
#include<sys/time.h>
#include<unistd.h>
#define _POSIX_C_SOURCE 200809L
using namespace std;
void *temp(void *a)
{
sleep(10);
pthread_exit(NULL);
}
void printtime(void *a)
{
	pthread_t x;
	pthread_create(&x,NULL,*temp,(void *)NULL);
	time_t rawtime;
	int *b =(int *)a;
	struct tm *timeinfo;
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	printf ( "Thread %d Current local time and date: %s\n", *b, asctime (timeinfo) );
}


void *checktime1(void *a)
{
	//pthread_join(adcs);
	int i;
	for(i=10;i>0;i--)
	{
	int *b= (int *)a;
	sleep(*b);
	printtime(a);
	}
	pthread_exit(NULL);
	
}

void *checktime2(void *a)
{
	int i=5;
	for(;i>0;i--){
	int *b= (int *)a;
	sleep(2);
	printtime(a);
	}
	pthread_exit(NULL);
}
int main()
{
//queue<int> EPS;
//queue<int> ADCS;
//queue<int> SPV;
int eps_id,adcs_id;
pthread_t eps,adcs;
int e,a,m;
e=1,a=2,m=0;
printtime((void*) &m);
//time((void*) &m);

eps_id = pthread_create(&eps,NULL,checktime1,(void*) &e);
adcs_id = pthread_create(&adcs,NULL,checktime2,(void*) &a);



pthread_join(eps,NULL);
pthread_join(adcs,NULL);


}

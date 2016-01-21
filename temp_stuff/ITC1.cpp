#include<stdio.h>
#include<iostream>
#include<queue>
#include<unistd.h>
#include<string.h>
#include"functions.h"


pthread_t obc,eps,spv;


int main()
{
	
	pthread_create(&spv,NULL, manager , NULL);
	pthread_create(&obc,NULL, *wait , (void*)"OBC");
	pthread_create(&eps,NULL, *wait , (void*)"EPS");
	pthread_join(spv,NULL);
	pthread_join(obc,NULL);	
	pthread_join(eps,NULL);	
}

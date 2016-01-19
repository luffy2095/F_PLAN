#include<stdio.h>
#include<iostream>
#include<queue>
#include<unistd.h>
#include<string.h>

using namespace std;
queue<int> SPV;
queue<int> OBC;
queue<int> EPS;
void *manager(void *a);
void ObcMsgHandler();
void EpsMsgHandler();
void *wait(void *a);
void *manager(void *a)
{
	int receiver;
	scanf("%d",&receiver);
	switch(receiver)
	{
	case 1:
		OBC.push(000);
		break;
	case 2:
		EPS.push(111);
		break;
	}
	manager((void *) NULL);
	
}
void ObcMsgHandler()
{
	string sub1;
	//, *sub2;
	sub1 = "OBC";
//	sub2 = "EPS";
	int msg = OBC.front();
	OBC.pop();
	printf("msg received: sender :- %d\n",msg);
	wait((void *)"OBC");

}
void EpsMsgHandler()
{
	string sub2;
	//, *sub2;
//	sub1 = "OBC";
	sub2 = "EPS";
	int msg = EPS.front();
	EPS.pop();
	printf("msg received: sender SPV : MSG :- %d\n",msg);
	wait((void *)"EPS");

}
void *wait(void *a)
{
	string sub1, sub2;
	sub1 = "OBC";
	sub2 = "EPS";
	char * SubSys = (char *)a;
	int T_name;
	if(SubSys=="OBC")
		{
			T_name = 1;
		}
	else if(SubSys=="EPS")
		{
			T_name = 2;
		}
	
	switch(T_name)
	{
		case 1 :
			if(OBC.empty())
				{
					sleep(1);
					wait((void*)"OBC");
				} 
			else
				{
					ObcMsgHandler();	
				}
			break;
		case 2 :
			if(EPS.empty())
				{
					sleep(1);
					wait((void*)"EPS");
				} 
			else
				{
					EpsMsgHandler();	
				}
			break;
	}
}
int main()
{
	pthread_t obc,eps,spv;
	string sub1, sub2;
	sub1 = "OBC";
	sub2 = "EPS";
	pthread_create(&spv,NULL, manager , NULL);
	pthread_create(&obc,NULL, *wait , (void*)"OBC");
	pthread_create(&eps,NULL, *wait , (void*)"EPS");
	pthread_join(spv,NULL);
	pthread_join(obc,NULL);	
	pthread_join(eps,NULL);	
}

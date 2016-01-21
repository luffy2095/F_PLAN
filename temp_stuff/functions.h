#include<stdio.h>
#include<iostream>
#include<queue>
#include<unistd.h>
#include<string.h>

using namespace std;
typedef struct message
{
	char receiver[10];
	int command;
} message;
int error_count=0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con=PTHREAD_COND_INITIALIZER;
queue<message> PERM_ERR;
queue<message> ERR;
queue<message> SPV;
queue<int> OBC;
queue<int> EPS;
void *manager(void *a);
void ObcMsgHandler();
void EpsMsgHandler();
void *wait(void *a);
void *manager(void *a)
{
	message send_msg;
	while(1)
	{
	scanf("%s %d", send_msg.receiver,&send_msg.command);
	if(send_msg.command == 0 || !strcmp(send_msg.receiver,"error") || !strcmp(send_msg.receiver,"ERROR"))
		{
		//printf("breaking");
		if(send_msg.command == 0 ){break;}
		else
			{
				SPV.push(send_msg);
				break;
			}
		
		}
	else
		{
	//		printf("pushing");
			SPV.push(send_msg);
		}
	}
	//printf("here");
	message temp;
	while(!SPV.empty())
	{
		//printf("in second");
		temp=SPV.front();
		SPV.pop();
		//printf("%s" , temp.receiver);
		if(!strcmp(temp.receiver,"EPS"))
			{
				//printf("EPS pushing");
				EPS.push(temp.command);
			}	
		else if(!strcmp(temp.receiver,"OBC"))
			{
				OBC.push(temp.command);
			}
		else if(!strcmp(temp.receiver,"error") || !strcmp(temp.receiver,"ERROR"))
			{
				if(ERR.empty())
					{
						printf("no Error detected");
					}
				else
					{
						while(!ERR.empty())
							{
								printf("Error!!! Receiver:- %s  Command:- %d :: Unknown receiver.\n",ERR.front().receiver,ERR.front().command);
								PERM_ERR.push(ERR.front());
								ERR.pop();
							}
						printf("Total error count : %d\n", error_count);
					}
			}
		else 
			{
				error_count++;
				ERR.push(temp);
			}
	}
	manager((void *) NULL);
	
}
void *wait(void *a)
{
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
					//printf("OBC Waiting \n");
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
					//printf("EPS Waiting \n");
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
void ObcMsgHandler()
{
	int msg = OBC.front();
	OBC.pop();
	printf("msg received: sender :- %d\n",msg);
	if(OBC.empty()){pthread_cond_signal(&con);}
	wait((void *)"OBC");

}
void EpsMsgHandler()
{
	if(!OBC.empty()){pthread_cond_wait(&con, &mut);}
	int msg = EPS.front();
	EPS.pop();
	printf("msg received: sender SPV : MSG :- %d\n",msg);
	//
	wait((void *)"EPS");

}


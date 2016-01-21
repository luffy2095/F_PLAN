#include<stdio.h>
#include<iostream>
#include<queue>
#include<unistd.h>
#include<string.h>
using namespace std;
void test_void(int sender,void *a);
void test1(int *b);
void test2(string b);

void test_void(int sender , void *a)
{
int *temp;
	switch(sender)
	{
		case(1):
			temp = (int *) a;
			printf("case 1: %d", *temp);
	}

}
void test1(int *b)
{
	test_void(1,(void *)b);
}
//void test2(string b)
//{
//	printf("%s",b.c_str());	
//	 //(void *)b;
////	test_void(2,arg);

//}
int main()
{
	//string a;
	//a="pra";
	int b;
	b=5;
	test1(&b);
	//test2(a);

}

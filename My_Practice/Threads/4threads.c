#include<stdio.h>
#include<pthread.h>

pthread_t tid[4];
unsigned int shared_data = 0;
pthread_mutex_t mutex;
unsigned int rc;
//prototypes for callback functions

void* PrintNo1(void*);
void* PrintNo2(void*);
void* PrintNo3(void*);
void* PrintNo4(void*);
//id* PrintOddNos(void*);
int value =1;

void main(void)
{
	pthread_create(&tid[0],0,&PrintNo1,0);
	pthread_create(&tid[1],0,&PrintNo2,0);
	pthread_create(&tid[2],0,&PrintNo3,0);
	pthread_create(&tid[3],0,&PrintNo4,0);
	sleep(3);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
}

void* PrintNo1(void *ptr)
{
	while(1)
	{
	value=1;
	rc = pthread_mutex_lock(&mutex);
	printf("%d\n",value);
	value++;	
	

 rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
	sleep(1);
	}
}

void* PrintNo2(void *ptr)
{
	while(1)
	{
	rc = pthread_mutex_lock(&mutex);
	//sleep(1);
	printf("%d\n",value);
	value++;

	 rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
	sleep(1);
	}
}
void* PrintNo3(void *ptr)
{
	//sleep(2);
	while(1)
	{
	 rc = pthread_mutex_lock(&mutex);
	printf("%d\n",value);
	value++;
	 rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
	sleep(1);
	}
}
void* PrintNo4(void *ptr)
{
	while(1)
	{
	     rc = pthread_mutex_lock(&mutex);
	//sleep(3);
	printf("%d\n",value);
	value++;
	rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
	sleep(1);
	}
}


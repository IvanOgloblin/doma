#include <sys/syscall.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<pthread.h>
#include<stdio.h>
//#include<limits.h>
//#include<unistd.h>
//#include<stdlib.h>
//#include<termios.h>
//pthread_mutex_t mut;
//#ifdef SYS_gettid

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
void *loader(void *c)
{
    time_t t;
    srand((unsigned) time(&t));    
    while(1)
    {
	sleep(1);
	int co=rand()%5;
	pthread_mutex_lock(&mut);
	int *ptr=(int*)c;
	ptr[co]+=500;
	printf("Loader: Ich come zu %d)einkaufen und hinzugefügt 500 Produkte.\n",co);
	pthread_mutex_unlock(&mut);
    }
}
void *consumer(void *c)
{	
	time_t t;
	srand((unsigned) time(&t));
	pid_t tid=syscall(SYS_gettid);
	int count=10000+rand()%1000;
	int co=rand()%5;
	int ex=0;
	while(ex==0)
	{
	    sleep(10);
	    co=rand()%5;
	    pthread_mutex_lock(&mut);
	    int *ptr=(int*)c;
	    if(ptr[co]<count)
	    {
		count-=ptr[co];
		printf("Consumer(%d): Ich kaufte %d Produkte im Geschäft %d. Rest: %d\n",tid,ptr[co],co,count);
		ptr[co]=0;
	    }
	    else
	    {
		ptr[co]-=count;
		printf("Consumer(%d): Ich kaufte %d Produkte im Geschäft %d.\n",tid,count,co);
		printf("Consumer(%d): Ich bin fertig\n",tid);
		ex=1;
	    }
	    pthread_mutex_unlock(&mut);
	}
}

int main()
{
    //pthread_mutex_init(&mutex, NULL);
    time_t t;
    srand((unsigned) time(&t));
    int shop[5];
    pthread_t lo;
    pthread_t co[3];
    int i=0;
    int status[3];
    /*for(i=0;i<100;i++)
    {
	printf("%d",rand()%5);
    }
    scanf("%d");*/
    for(i=0;i<5;i++)
    {
	shop[i]=950+rand()%100;
    }
    pthread_create(&lo,NULL,loader,(void*)shop);
    for(i=0;i<3;i++)
    {
	pthread_create(&co[i],NULL,consumer,(void*)shop);
    }
    for(i=0;i<3;i++)
    {
	pthread_join(co[i],(void**)&status[i]);
    }
    pthread_cancel(lo);
    printf("EXIT");
    exit(0);
}
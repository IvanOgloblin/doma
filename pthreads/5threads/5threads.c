#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<pthread.h>
#include<stdio.h>
void *func(void *c)
{
    int *ptr=(int*)c;
    printf("%d\n",*ptr);
    pthread_exit(0);
}

int main()
{
    pthread_t th[5];
    int i=0;
    int status[5];
    int mass[5];
    for(i=1;i<6;i++)
    {
	mass[i-1]=i;
	pthread_create(&th[i-1],NULL,func,(void*)&mass[i-1]);
    }
    
    for(i=0;i<5;i++)
    {
	int c=0;
	pthread_join(th[i],(void**)&status[i]);
    }
    return 0;
}
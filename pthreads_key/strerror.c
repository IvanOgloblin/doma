#include<pthread.h>
#include<stdio.h>
#include<string.h>

pthread_key_t key;
pthread_once_t once=PTHREAD_ONCE_INIT;

void dest(void *buf)
{free(buf);}

void key_creat(void)
{pthread_key_create(&key,dest);}

void *strerr(int error)
{
    char *buf;
    int status=pthread_once(&once,key_creat);
    buf=pthread_getspecific(key);
    if(buf==NULL)
    {
	buf=malloc(100);
	pthread_setspecific(key,buf);
    }
    strncpy(buf,strerror(error),100);
    return buf;
}
int main()
{
    printf("%s",strerr(7));
}
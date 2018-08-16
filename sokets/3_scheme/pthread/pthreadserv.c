#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>

void *func(void *c)
{
    int sock=*(int*)c;
    long int ttime;
    ttime = time(NULL);
    char message=ctime(&ttime);
    send(sock, ttime, sizeof(ttime), 0);
    printf("Отправил");
    pthread_exit(0);
}


int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15225);
    addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
	perror("bind");
        exit(2);
    }
    listen(listener, 5);
    /*if(recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *) &client,&client_address_size) <0)
    {
        printf("recvfrom()");
        exit(4);
    }*/
    //while(1)
    //{
    long count=0;
    while(1)
    {
	pthread_t th;
	int status;
	count++;
	sock = accept(listener, (struct sockaddr*)NULL, NULL);
	if(sock < 0)
	{
	    perror("accept");
    	    exit(3);
	}
	/*if(recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *) &client,&client_address_size) <0)
	{
    	    printf("recvfrom()");
    	    exit(4);
	}*/
	pthread_create(&th,NULL,func,(void*)&sock);
	pthread_join(th,(void**)&status);
	printf("%d\n",count);
    }
    exit(0);
}

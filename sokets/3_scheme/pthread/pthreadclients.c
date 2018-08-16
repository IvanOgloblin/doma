#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void *func()
{	
	long *buf;
	int sock;
	struct sockaddr_in addr;
	//sock = socket(AF_INET, SOCK_STREAM, 0);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
	    perror("socket");
	    exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(15225);
	addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
    
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
	    perror("connect");
    	    exit(2);
	}
	/*if (sendto(sock, NULL, NULL, 0,(struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
	    printf("sendto()");
	    exit(2);
	}*/
	                                                        
	recv(sock, buf, sizeof(long), 0);
	printf("accept");
	close(sock);
	
	pthread_exit(0);
}


int main()
{
    while(1)
    {
	pthread_t th;
	int status;
	pthread_create(&th,NULL,func,NULL);
	pthread_join(th,(void**)&status);
    }
    exit(0);
}

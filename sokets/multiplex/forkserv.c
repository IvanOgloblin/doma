#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
int main()
{
    int sockudp,socktcp, listener,client_address_size;
    struct sockaddr_in addr, client;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    sockudp = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockudp < 0)
    {
        perror("socket");
        exit(1);
    }
                                                                        
    addr.sin_family = AF_INET;
    addr.sin_port = htons(15302);
    addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
    
    
	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
	    perror("bind listener");
    	    exit(2);
	}
	listen(listener, 5);
	if(bind(sockudp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
    	    perror("bind");
    	    exit(2);
	}
	client_address_size = sizeof(client);
	fd_set fds;
	struct timeval tv;
	FD_ZERO(&fds);
	FD_SET(listener, &fds);
	FD_SET(sockudp, &fds);
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	if(listener>sockudp)
	{
	    if(select(listener, &fds, NULL, NULL, NULL)==-1)
	    {
		printf("error select");
		exit(0);
	    }
	}
	else
	{
	    if(select(sockudp, &fds, NULL, NULL, NULL)==-1)
	    {
		printf("error select");
		exit(0);
	    }
	}
	for(;;)
	{
	    if(FD_ISSET(listener,&fds))
	    {
		long int ttime;
		socktcp = accept(listener, (struct sockaddr*)NULL, NULL);
		if(socktcp < 0)
		{
		    perror("accept");
    		    exit(3);
		}
		recv(socktcp, ttime, sizeof(ttime), 0);
		printf ("TCP Время получено: %s\n",ctime (&ttime) );
		close(socktcp);
	    }
	    if(FD_ISSET(sockudp,&fds))
	    {
		long int ttime;
		if(recvfrom(sockudp, ttime, sizeof(ttime), 0, (struct sockaddr *) &client,&client_address_size) <0)
		{
	    	    printf("recvfrom()");
	    	    exit(4);
		}	
	                                                             
		printf ("TCP Время получено: %s\n",ctime (&ttime) );
	    }
	}
    exit(0);
}

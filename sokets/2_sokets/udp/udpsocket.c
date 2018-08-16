#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
    pid_t pid;
    int rv;
    switch(pid=fork()) 
    {
	case -1:
	    perror("fork"); /* произошла ошибка */
	    exit(1); /*выход из родительского процесса*/
	case 0:
	{
	    char *message = "Hello there!\n";
	    char buf[sizeof(message)];
	    int sock;
	    struct sockaddr_in addr;
	    sock = socket(AF_INET, SOCK_DGRAM, 0);
	    if(sock < 0)
	    {
		perror("socket");
		exit(1);
	    }
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(15226);
	    addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
	    
	    if (sendto(sock, message, (strlen(message)+1), 0,(struct sockaddr *)&addr, sizeof(addr)) < 0)
	    {
	        printf("sendto()");
	        exit(2);
	    }
	    if(recv(sock, buf, sizeof(message), 0) <0)
	    {
	        printf("recvfrom()");
	        exit(4);
	    }
	    printf("changemessage: ");
	    printf(buf);
	    /*if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	    {
		perror("connect");
	        exit(2);
	    }
	    sleep(3);
	    send(sock, message, sizeof(message), 0);
	    //printf("Клиент: Принял");
	    sleep(1);
	    recv(sock, buf, sizeof(message), 0);
	    //printf("Клиент: Отправил");
	    printf(buf);	    
	    //close(sock);*/
	    exit(rv);
	}
	default:
	{
	    int sock, listener, client_address_size;
	    struct sockaddr_in addr, client;
	    char buf[1024];
	    int bytes_read;
	    listener = socket(AF_INET, SOCK_DGRAM, 0);
	    if(listener < 0)
	    {
	        perror("socket");
	        exit(1);
	    }
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(15226);
	    addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_ANY);
	    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	    {
		perror("bind");
	        exit(2);
	    }
	    client_address_size = sizeof(client);
	    if(recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *) &client,&client_address_size) <0)
	    {
	        printf("recvfrom()");
	        exit(4);
	    }
	    printf("Received message %s from domain %s port %d internet\n",buf,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	    ntohs(client.sin_port));
	    char *ch="Y";
	    buf[0]=*ch;
	    sleep(1);
	    if (sendto(listener, buf, (strlen(buf)+1), 0,(struct sockaddr *)&client, sizeof(client)) < 0)
	    {
	        printf("sendto()");
	        exit(2);
	    }
	    
	    /*
	    listen(listener, 5);
	    //while(1)
	    //{
		sock = accept(listener, (struct sockaddr*)NULL, NULL);
	        if(sock < 0)
	        {
	    	    perror("accept");
	            exit(3);
	        }
	        //while(1)
	        //{
	    	    bytes_read = recv(sock, buf, 1024, 0);
	    	    //printf("Сервер: Принял");
	            //if(bytes_read <= 0) break;
	        //}
	        char *c="Y";
	        buf[0]=*c;
	        send(sock, buf, bytes_read, 0);
	        //printf("Сервер: Отправил");
		close(sock);
	    //}*/
		wait(0);
		close(listener);
	}
    }
    exit(0);
}

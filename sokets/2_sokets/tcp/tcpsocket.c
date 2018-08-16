#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
    pid_t pid;
    int rv;
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
	    addr.sin_port = htons(15228);
	    inet_aton("192.168.2.111",&addr.sin_addr);
	    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	    {
		perror("bind");
	        exit(2);
	    }
	    listen(listener, 5);
	    sock = accept(listener, (struct sockaddr*)NULL, NULL);
	    sleep(10);
	        
    exit(0);
}

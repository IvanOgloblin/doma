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
    while(1)
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
		char *buf;
		int sock;
		struct sockaddr_in addr;
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
		    perror("socket");
		    exit(1);
		}
		addr.sin_family = AF_INET;
		addr.sin_port = htons(15226);
		addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
	    
		if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
		    perror("connect");
	    	exit(2);
		}
		recv(sock, buf, sizeof(char)*20, 0);
		printf(buf);	    
		close(sock);
		exit(rv);
		}
	        //default:
	        //{
	        //}
	}
    }
    exit(0);
}

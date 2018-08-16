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
    addr.sin_port = htons(15226);
    addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
	perror("bind");
        exit(2);
    }
    listen(listener, 5);
    //while(1)
    //{
    long count=0;
    while(1)
    {
	count++;
	sock = accept(listener, (struct sockaddr*)NULL, NULL);
	if(sock < 0)
	{
	    perror("accept");
    	    exit(3);
	}
	pid_t pid;
	int rv;
	switch(pid=fork()) 
	{
	    case -1:
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	    case 0:
	    {
		long int ttime;
		ttime = time(NULL);
		char message=ctime(&ttime);
		send(sock, message, sizeof(message), 0);
		printf("Отправил");
		exit(rv);
	    }
	//default:
	//{
	//}
	}
	printf("%d\n",count);
    }
    exit(0);
}

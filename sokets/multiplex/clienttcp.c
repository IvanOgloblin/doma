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
while(1)
{
int sock;
struct sockaddr_in addr;
sock = socket(AF_INET, SOCK_STREAM, 0);
if(sock < 0)
{
	perror("socket");
	exit(1);
}
addr.sin_family = AF_INET;
addr.sin_port = htons(15302);
addr.sin_addr.s_addr = htonl(/*127.0.0.1);*/INADDR_LOOPBACK);
long int ttime;
ttime = time (NULL);
if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
{
	perror("connect");
        exit(2);
}
send(sock, ttime, sizeof(ttime), 0);
}
exit(0);
}

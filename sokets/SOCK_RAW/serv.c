#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main()
{
	struct sockaddr_in serv, client; 
	int dest = 30002;
	int sock; 
	char buf[100];
	
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(dest);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (struct sockaddr *)&serv, sizeof(serv));
	
	fflush(stdout);
	int client_leng = sizeof(client);
	while(1)
	{
		if( recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_leng)>0)
		{
			printf("Resived: %s", buf);
				buf[0] = 'Y';
			sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client, sizeof(client));
		}
	
	}
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

struct udppacket
{
	short int sour;
	short int dest;
	short int leng;
	short int csum;
	char data[21];
};

int main()
{
	struct sockaddr_in serv, client;
	struct udppacket up;
	int sock;
	short dest = 30002, sour = 31000;
	char data[21], buf[100];

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(dest);
	inet_aton("127.0.0.1", &serv.sin_addr);
	memset(data, '0', sizeof(data));
	memset(buf, '0', sizeof(buf));

	up.sour= htons(sour);
	up.dest = htons(dest);
	up.leng = htons(29);
	up.csum = 0;	
	strncpy(up.data, "Hello world I am G1S\0", sizeof(up.data));
		
	int client_leng = sizeof(client);
	if (sendto(sock, &up, sizeof(up), 0, (struct sockaddr *)&serv, sizeof(serv)) < 0)
	{
	    perror("Sendto");
	    exit(1);
	}
	while(1)
	{
	    recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_leng);
	    struct udphdr *upi = (struct udphdr* )(buf+20);
	    char *data = buf+28;		
	    if (upi->dest == htons(sour))
	    {
		FILE *f = fopen("sniffer.txt", "a");
		printf("data recived");
		fprintf(f,"Received message %s from domain %s port sour%d port dest%d IP %s\n\n",data,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(client.sin_port),ntohs(upi->source),inet_ntoa(client.sin_addr));
		exit(0);
	    }
	}
	exit(0);
}

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

struct ippacket
{
	unsigned char hlen:4;
	unsigned char ver:4;
	unsigned char tos;
	unsigned short leng;
	unsigned short id;
	unsigned short flfr;
	unsigned char ttl;
	unsigned char prot;
	unsigned short csum;
	unsigned int sour;
	unsigned int dest;
	struct udppacket up;
};

unsigned short get_chksum(unsigned short *ptr, int nbytes)
{
	register long sum;
	u_short oddbyte;
        register u_short answer;
        sum = 0;
        while (nbytes > 1) 
        {
    	    sum += *ptr++;
    	    nbytes -= 2;
        }
                                    
        if (nbytes == 1) 
        {
    	    oddbyte = 0;
    	    *((u_char *) & oddbyte) = *(u_char *) ptr;
    	    sum += oddbyte;
        }
                                                                        
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
        answer = ~sum;
                                                                                    
        return (answer);
}

int main()
{
	struct sockaddr_in serv, client;
	struct ippacket ip;
	int sock;
	short dest = 30002, sour = 31000;
	char data[21], buf[100];

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	int val = 1;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL,(const char *)&val, sizeof(val));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(dest);
	inet_aton("127.0.0.1", &serv.sin_addr);
	memset(data, '0', sizeof(data));
	memset(buf, '0', sizeof(buf));

	ip.ver=4;
	ip.hlen=5;
	ip.tos=0;
	ip.leng=49;
	ip.id=7;
	ip.flfr=0;
	ip.ttl=64;
	ip.prot=17;
	ip.csum=get_chksum((unsigned short*) &ip, sizeof(ip));
	ip.sour=inet_addr("127.0.0.1");
	ip.dest=inet_addr("127.0.0.1");
	ip.up.sour= htons(sour);
	ip.up.dest = htons(dest);
	ip.up.leng = htons(29);
	ip.up.csum = 0;	
	strncpy(ip.up.data, "Hello world I am G1S\0", sizeof(ip.up.data));
		
	int client_leng = sizeof(client);
	if (sendto(sock, &ip, sizeof(ip), 0, (struct sockaddr *)&serv, sizeof(serv)) < 0)
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
		FILE *f = fopen("sniffer_ip.txt", "a");
		printf("data recived");
		fprintf(f,"Received message %s from domain %s port sour%d port dest%d IP %s\n\n",data,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(client.sin_port),ntohs(upi->source),inet_ntoa(client.sin_addr));
		exit(0);
	    }
	}
	exit(0);
}

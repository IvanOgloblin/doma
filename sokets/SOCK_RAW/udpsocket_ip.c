#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<netinet/udp.h>
#include <netinet/ip.h>

struct udppacket
{
    short int sour;
    short int dest;
    short int summ;
    short int leng;
    char payl[15];
};

struct ippacket
{
unsigned char version:4;
unsigned char ihl:4;
unsigned char tos;
unsigned short len;//=5;
unsigned short id;//=0;
unsigned short frag_off;//=0;
unsigned char ttl;//=64;
unsigned char protocol;//=17;
unsigned short check;//=0;
unsigned int saddr;
unsigned int daddr;
struct udppacket up;
};



int main()
{
	struct ip *myip;
	struct udphdr *myudp;
	struct sockaddr_in sin, client;
	char *payload="Hello world!";
	struct udppacket up;
	struct ippacket ip;
	bzero((char* )&up,sizeof(up));
	bzero((char* )&ip,sizeof(ip));
	strcpy(up.payl,"Hello world!");
	up.sour=htons(1111);
	up.dest=htons(1111);
	up.summ=0;
	up.leng=(sizeof(up.payl)+sizeof(up.sour)+sizeof(up.dest)+sizeof(up.summ)+sizeof(up.leng));//странно здесь говорит 23
	up.leng=sizeof(up);//а здесь 24
	printf("%d",up.leng);
	ip.up=up;
	ip.version=4;
	ip.len=5;
	ip.ttl=64;
	ip.protocol=17;
	printf("%s",ip.up.payl);
	sin.sin_family=AF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr =inet_addr("127.0.0.1");
	
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
	int val=1;
	setsockopt(s,IPPROTO_IP,IP_HDRINCL,&val,sizeof(val));
	sendto(s,&ip,sizeof(ip),0,(struct sockaddr *)&sin, sizeof(sin));
	
	
    	    int i=0;
            FILE *f = fopen("sniffer_ip.txt", "w");
            for(i=0;i<1;i++)
            {
        	struct udppacket *upi;
        	char buf[100];
        	int len=sizeof(client);
                if((recvfrom(s, buf, 100, 0, (struct sockaddr *)&client, &len)) <0)
                {
                    perror("recvfrom()");
                    exit(4);
                }
                upi=buf+20;
                char *ch;
                inet_ntoa(ch,sin.sin_addr);
                fprintf(f,"Received message %s from domain %s port sour%d port dest%d IP %s\n\n",upi->payl,(sin.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(sin.sin_port),ntohs(upi->sour),ch);
                                                                                                                                                                                                                                                                                    
            }
            fclose(f);
            
	    exit(0);
}

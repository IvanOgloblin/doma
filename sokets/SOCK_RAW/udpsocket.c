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

int main()
{
	struct ip *myip;
	struct udphdr *myudp;
	struct sockaddr_in sin, client;
	char *payload="Hello world!";
	struct udppacket up;
	bzero((char* )&up,sizeof(up));
	strcpy(up.payl,"Hello world!");
	up.sour=htons(1111);
	up.dest=htons(1111);
	up.summ=0;
	up.leng=(sizeof(up.payl)+sizeof(up.sour)+sizeof(up.dest)+sizeof(up.summ)+sizeof(up.leng));//странно здесь говорит 23
	up.leng=sizeof(up);//а здесь 24
	printf("%d",up.leng);
	sin.sin_family=AF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr =inet_addr("127.0.0.1");
	
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
	
	sendto(s,&up,up.leng,0,(struct sockaddr *)&sin, sizeof(sin));
	
	
    	    int i=0;
            FILE *f = fopen("sniffer.txt", "w");
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

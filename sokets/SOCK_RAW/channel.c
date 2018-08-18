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

struct ethernetpacket
{
    char preamb[8];
    char dest[6];
    char sour[6];
    short type;
    struct ippacket ip;
    int FCS;
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
	struct sockaddr_ll serv, client;
	struct ethernetpacket ep;
	int sock;
	short dest = 30002, sour = 31000;
	char data[21], buf[100];

	sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	memset((void *)&serv, 0, sizeof(struct sockaddr_ll));
	int val = 1;
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL,(const char *)&val, sizeof(val));
	serv.sll_family = AF_PACKET;
	serv.sll_protocol = htons(ETG_P_ALL);
	serv.sll_ifindex = if_nametoindex(eth0);
	serv.halen=6;
	serv.sll_addr[0]=0xA0;
	serv.sll_addr[1]=0xAB;
	serv.sll_addr[2]=0x1B;
	serv.sll_addr[3]=0xD0;
	serv.sll_addr[4]=0x12;
	serv.sll_addr[5]=0x6D;
	//inet_aton("127.0.0.1", &serv.sin_addr);
	memset(data, '0', sizeof(data));
	memset(buf, '0', sizeof(buf));
	//_____________________________test_______________________
	
	
	//________________________________________________________
	//ep.pream=
	ep.sour[0]=0x00;
	ep.sour[1]=0x25;
	ep.sour[2]=0x22;
	ep.sour[3]=0x01;
	ep.sour[4]=0x75;
	ep.sour[5]=0xAA;
	
	ep.dest[0]=0xA0;
	ep.dest[1]=0xAB;
	ep.dest[2]=0x1B;
	ep.dest[3]=0xD0;
	ep.dest[4]=0x12;
	ep.dest[5]=0x6D;
	
	
	ep.type=0x0800;
	ep.csum=get_chksum((unsigned short*) &ep+8, 47);
	ep.ip.ver=4;
	ep.ip.hlen=5;
	ep.ip.tos=0;
	ep.ip.leng=49;
	ep.ip.id=7;
	ep.ip.flfr=0;
	ep.ip.ttl=64;
	ep.ip.prot=17;
	ep.ip.csum=get_chksum((unsigned short*) &ip, sizeof(ip));
	ep.ip.sour=inet_addr("127.0.0.1");
	ep.ip.dest=inet_addr("127.0.0.1");
	ep.ip.up.sour= htons(sour);
	ep.ip.up.dest = htons(dest);
	ep.ip.up.leng = htons(29);
	ep.ip.up.csum = 0;
	strncpy(ep.ip.up.data, "Hello world I am G1S\0", sizeof(ep.ip.up.data));
		
	int client_leng = sizeof(client);
	if (sendto(sock, &ep, sizeof(ip), 0, (struct sockaddr *)&serv, sizeof(serv)) < 0)
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

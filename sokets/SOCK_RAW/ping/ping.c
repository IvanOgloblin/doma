#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
 
//заголовок ICMP  
struct icmppacket /* icmp header */
{
    unsigned char icmp_type;    /* icmp service type */
                        	/* 8 echo require, 0 echo reply */
    unsigned char icmp_code;    /* icmp header code */
    unsigned short icmp_chksum; /* icmp header chksum */
    unsigned short icmp_id;     /* icmp packet identification */
    unsigned short icmp_seq;    /* icmp packet sequent */
    unsigned char icmp_data[56]; /* icmp data, use as pointer */
};
 
// функция рачета  контрольной суммы. Исходник взят у У. Р. Стивенса (царство ему небесное)
//но алгоритм довольно простой и известный
 
unsigned short in_cksum(unsigned short *addr, int len)
{
    int             nleft = len;
    int             sum = 0;
    unsigned short  *w = addr;
    unsigned short  answer = 0;
 
    while (nleft > 1)  
    {
        sum += *w++;
        nleft -= 2;
    }
 
        /* 4mop up an odd byte, if necessary */
    if (nleft == 1) 
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w ;
        sum += answer;
    }
 
        /* 4add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
    sum += (sum >> 16);         /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return(answer);
}
 
 
 
int main()
{
while(1)
{
int s;
struct sockaddr_in serv,client;
struct icmppacket  icmp, *picmp;
int siz;
int len;
int flag=0;
char buf[255];
pid_t pid;
    
    pid=getpid();
    s=socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(s<0){
        printf("socket error\n");
        return 1;
    }
    bzero(&serv, sizeof(serv));
    
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("192.168.2.101");  
    
    
    icmp.icmp_type = 8;         // 8 - реквест ; 0 - реплай
    icmp.icmp_code = 0;         // код  
    icmp.icmp_id = pid;         // чаще всего сдесь именно идентификатор процесса
    icmp.icmp_seq = 1;          // порядковый номер пакета - при дальнейшей отправке увеличивай на 1
    gettimeofday((struct timeval *) icmp.icmp_data, NULL);  //  в данные занесём текущее время
                                //(по rfc отвечающий не должен изменять это поле и
                                // легко вычислить потом время хождения пакета)
 
    len = sizeof(icmp);     /* checksum ICMP header and data */
    icmp.icmp_chksum = 0;
    icmp.icmp_chksum = in_cksum((u_short *) &icmp, len); // расчет контроьной суммы -
 
    sendto(s, &icmp, sizeof(icmp), 0, (struct sockaddr *)&serv, sizeof(serv)); // посылаем
    int err;
    sleep(2);
    int client_leng=sizeof(client);
    err=recvfrom(s, buf, 255, MSG_DONTWAIT,(struct sockaddr *)&client, &client_leng);
    recvfrom(s, buf, 255, 0,(struct sockaddr *)&client, &client_leng);
    picmp = &buf[20];      
    flag = ( (0 == picmp->icmp_type) && pid == picmp->icmp_id); // если это наш пакет и это ответ -
    if(flag)
	printf("Пинг %s пингует!\n\n",inet_ntoa(client.sin_addr));
    else 
	printf("Нет ответа\n\n");
	fflush(stdout);
	sync();
    
}
}
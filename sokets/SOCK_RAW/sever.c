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
int sock, listener, client_address_size;
            struct sockaddr_in addr, client;
            char buf[1024];
            int bytes_read;
            listener = socket(AF_INET, SOCK_DGRAM, 0);
            if(listener < 0)
            {
                perror("socket");
                exit(1);
            }
            addr.sin_family = AF_INET;
            addr.sin_port = htons(1111);
            addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
            {
                perror("bind");
                exit(2);
            }
            client_address_size = sizeof(client);
		if((recvfrom(listener, buf, 100, 0, (struct sockaddr *)&client, &client_address_size)) <0)
		{
		    perror("recvfrom()");
		    exit(4);
		}
		                                                                         
            /*if(recvfrom(listener, buf, sizeof(buf), 0, (struct sockaddr *) &client,&client_address_size) <0)
            {
                printf("recvfrom()");
                exit(4);
            }*/
            printf("Received message %s from domain %s port %d internet\n",buf,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
            ntohs(client.sin_port));
            char *ch="Y";
            buf[0]=*ch;
            sleep(1);
            if (sendto(listener, buf, (strlen(buf)+1), 0,(struct sockaddr *)&client, sizeof(client)) < 0)
            {
                printf("sendto()");
                exit(2);
            }
            return 0;

}
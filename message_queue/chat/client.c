#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
struct mesg_buffer 
{
    long mesg_type;
    long num;
    char mesg_text[100];
    char nik[100];
}message;


/*int main()
{
    struct msqid_ds msqid_ds, *buf;
    printf("My pid:%d\n",getpid());
    buf = &msqid_ds;
    key_t key;
    int msgid;
    int count=2;
    char nik[100];
    printf("Inter nik:");
    scanf("%s",nik);
    printf("\n");
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666|IPC_CREAT);
    message.mesg_type = 1;
    msgsnd(msgid, &message, sizeof(message), IPC_NOWAIT);
    printf("%s",strerror(errno));
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    int num=message.num;
    pid_t pid;
    int rv;
    int rp;
    switch(pid=fork())
    {
	case -1:
        perror("fork"); 
        exit(1);
        case 0:
        {
    	    while(1){
    	    msgrcv(msgid, &message, sizeof(message), num, 0);
    	    printf("Nik: %s. Message: %s",message.nik,message.mesg_text);
    	    }
        }
        default:
        {	
    	    while(1){
    	    scanf("%s",message.mesg_text);
    	    int compareLimit = 4;
    	    int result = strncmp(message.mesg_text, "exit", compareLimit);
    	    if(result==0)
    	    {	
    		kill(pid, SIGKILL);
    		exit(0);
    	    }
    	    message.mesg_type = num;
    	    strncpy (message.nik, nik,100);
    	    msgsnd(msgid, &message, sizeof(message), num);
    	    }
        }
    }
}*/



int main()
{
long num;
char nik[100];
printf("Inter NIK: ");
scanf("%s",nik);
printf("\n");
key_t key;
int msgid;
key = ftok("progfile", 65);
msgid = msgget(key, 0666|IPC_CREAT);
message.mesg_type = 1;
strncpy (message.nik, nik,100);
//msgctl(msgid, IPC_RMID, NULL);

msgsnd(msgid, &message, sizeof(message), IPC_NOWAIT);
msgrcv(msgid, &message, sizeof(message), 2, 0);
num=message.num;
int ex=0;
while(!ex)
{
    printf("1.Написать сообщение\n");
    printf("2.Посмотреть новые сообщения\n");
    printf("3.Выход\n");
    int c;
    scanf("%d",&c);
    switch(c)
    {
        case 2:
        {
    	    printf("Новые сообщения: \n");
    	    while(msgrcv(msgid, &message, sizeof(message), num, IPC_NOWAIT)>=0)
    	    {
    		printf("Nik: %s. Message: %s.\n",message.nik,message.mesg_text);
    	    }
    	    break;
    	}
    	case 1:
    	{
    	    scanf("%s",message.mesg_text);
    	    strncpy (message.nik, nik,100);
    	    message.mesg_type=3;
    	    msgsnd(msgid, &message, sizeof(message), IPC_NOWAIT);
    	    break;
    	}
    	case 3:
    	{
    	    exit(0);
    	}
    }
}
}
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
struct mesg_buffer 
{
    long mesg_type;
    long num;
    char mesg_text[100];
    char nik[100];
}message;


int main()
{
    //struct msqid_ds msqid_ds, *buf;
    printf("My pid:%d\n",getpid());
    //buf = &msqid_ds;
    key_t key;
    int msgid;
    int count=4;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 2;
    while(1)
    {
	if(msgrcv(msgid, &message, sizeof(message), 1, IPC_NOWAIT)>=0)
	{
	    message.num=count;
	    message.mesg_type=2;
	    msgsnd(msgid, &message, sizeof(message), 0);
	    count++;
	}
	else
	{
	    if(msgrcv(msgid, &message, sizeof(message), 3, IPC_NOWAIT)>=0)
	    {	
		int i;
		for(i=4;i<count;i++)
		{
		    message.mesg_type=i;
		    msgsnd(msgid, &message, sizeof(message), 0);
		}
	    }
	}
    }
    msgctl(msgid, IPC_RMID, NULL);
    
    exit(0);
}
#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf
{
    long mesg_type;
    char mesg_text[100];
}message;

int main()
{
pid_t pid;
int rv;
int rp;
switch(pid=fork()) 
{
    case -1:
    perror("fork"); /* произошла ошибка */
    exit(1); /*выход из родительского процесса*/
    case 0:{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    printf("Write Data : ");
    gets(message.mesg_text);
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("%d",errno);
    printf("Data send is : %s \n", message.mesg_text);
    exit(rv);}
    default:{
    key_t key2;
    int msgid2;
    key2 = ftok("progfile", 65);
    msgid2 = msgget(key2, 0666 | IPC_CREAT);
    msgrcv(msgid2, &message, sizeof(message), 1, 0);
    printf("Data Received is : %s \n", message.mesg_text);
    msgctl(msgid2, IPC_RMID, NULL);
    exit (0);}
}
}
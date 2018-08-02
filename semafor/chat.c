#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
struct mesg_buffer 
{
    //long mesg_type;
    long num;
    char mesg_text[100];
    char nik[100];
}MESSAGE;




int main()
{
    printf("My pid:%d\n",getpid());
    key_t key;
    struct sembuf lock[2];//={0,0,0,0,1,0};
    struct sembuf unlock;//={0,-1,0};
    
    lock[0].sem_num=0;
    lock[0].sem_op=0;
    lock[0].sem_flg=0;
    lock[1].sem_num=0;
    lock[1].sem_op=1;
    lock[1].sem_flg=0;
    
    unlock.sem_num=0;
    unlock.sem_op=-1;
    unlock.sem_flg=0;
    
    int shmid;
    int semid;
    char nik[100];
    printf("Inter NIK: ");
    scanf("%s",nik);
    printf("\n");
    struct mesg_buffer *shmbuff;
    key = ftok("progfile", 65);
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid < 0) 
    {
	printf("Error - %s\n", strerror(errno));
        exit(-1);
    }
    shmid = shmget(key,sizeof(MESSAGE)*1000,0666 | IPC_CREAT);
    if((shmid = shmget(key, sizeof(MESSAGE)*1000, 0)) < 0)
    {
	printf("Can\'t find shared memory\n");
	exit(-1);
    }
    if((shmbuff = (struct MESSAGE *)shmat(shmid, NULL, 0)) == (int *)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    int ex=0;
    //semctl(semid,0,IPC_RMID,0);
    while(!ex)
    {
	printf("1.Написать сообщение\n");
	printf("2.Посмотреть сообщения\n");
	printf("3.Выход\n");
	int c;
	scanf("%d",&c);
	switch(c)
	{
	    case 1:
		{
		    int i;
		    char mess[100];
		    printf("Inter message:");
		    scanf("%s",mess);
		    printf("\n");
		    for(i=0;i<1000;i++)
		    {
			if(shmbuff[i].num==0)
			{
			    semop(semid,lock,2);
			    strncpy(shmbuff[i].nik,nik,100);
			    strncpy(shmbuff[i].mesg_text,mess,100);
			    shmbuff[i].num=1;
			    if(i<999)
			    shmbuff[i+1].num=0;
			    else
			    shmbuff[0].num=0;
			    i=0;
			    semop(semid,&unlock,1);
			    break;
			}
		    }
		    break;
		}
	    case 2:
		{
		    int i;
		    for(i=0;i<1000;i++)
		    {
			semop(semid,lock,2);
			if(shmbuff[i].num!=0)
			{
			    printf("Nik: %s. Message: %s\n",shmbuff[i].nik,shmbuff[i].mesg_text);
			}
			semop(semid,&unlock,1);
		    }
		    break;
		}
	    case 3:
		{
		    exit(0);
		}
	}
    }
    exit(0);
}
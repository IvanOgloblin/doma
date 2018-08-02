#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
//#include<io.h>
int main()
{
    char *str="ls -la -p|cut";
    //    while(!ex)
    //    {
    //fflush(stdin);
            printf("Inter comand: ");
                    //scanf("%s",str);
                        //    gets(str);
    int fdi;
    int fdo;
    if(pipe(&fdo) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    if(pipe(&fdi) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    //char *command;
    //printf("Inter comand: \n");
    //gets(command);
                             
    int ex=0;
    
    while(!ex)
    {
	char sep[5]="|";
	char *istr;
	char *commands[10];
	int countcomm=0;
	istr = strtok (str,sep);
	while (istr!= NULL)
	{
	    commands[countcomm]=istr;
	    countcomm++;
	    istr = strtok (NULL,sep);
	}
	int i;
	for(i=0;i<=countcomm;i++)
	{
	    char *argv[10];
	    char *com;
	    char *namef;
	    istr = strtok (commands[i]," ");
	    namef = istr;
	    int countarg=0;
	    while(istr != NULL)
	    {
		istr=strtok(NULL," ");
		argv[countarg]=istr;
		countarg++;
	    }
	    
	    
	    pid_t pid;
	    switch(pid=fork()) 
	    {
		case -1:
		    perror("fork"); /* произошла ошибка */
		    exit(1); /*выход из родительского процесса*/
		case 0:
		    if(i%2==0)
		    {
			dup2(fdo,1);
			dup2(fdi,0);
		    }
		    else
		    {
			dup2(fdi,1);
			dup2(fdo,0);
		    }
		    execv(namef,argv);
		
		default:
		    wait(0);
		    break;
	    }
	}
	
	char string[1000];
	if(i%2==0)
	{
	    if(read(fdo, string, 100) < 0)
	    {
		printf("Can\'t read string\n");
		exit(-1);
	    }
	}
	else
	{
	    if(read(fdi, string, 100) < 0)
	    {
		printf("Can\'t read string\n");
		exit(-1);
	    }
	}
	printf("%s", string);
	exit(0);
	return 0;
	
	
	
	
	
    }
}

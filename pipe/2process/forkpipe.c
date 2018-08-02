#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
pid_t pid;
int fd[2];
if(pipe(fd) < 0)
{
    printf("Can\'t create pipe\n");
    exit(-1); 
}
int rv;
int rp;
switch(pid=fork()) {
case -1:
    perror("fork"); /* произошла ошибка */
    exit(1); /*выход из родительского процесса*/
case 0:
    printf(" CHILD: Мой PID -- %d\n", getpid());
    if(close(fd[1]) < 0)
    {printf("Can\'t close input stream\n");}
    char resstring[14];
    if(read(fd[0], resstring, 14) < 0)
    {
	printf("Can\'t read string\n"); 
	exit(-1); 
    }
    printf(" CHILD: Принятая строка -- %s\n", resstring);
    exit(rv);
default:
    printf("PARENT: Мой PID -- %d\n", getpid());
    if(close(fd[0]) < 0)
    {printf("Can\'t close input stream\n");}
    char string[] = "Hello, world!";
    if(write(fd[1], string, sizeof(string)) != 14)
    {
	printf("Can\'t write all string\n"); 
	exit(-1); 
    }
    printf("PARENT: Отправленая строка -- %s\n", string);
    waitpid(pid,rp,0);
    printf("PARENT: Код возврата потомка:%d\n",WEXITSTATUS(rv));
    printf("PARENT: Выход!\n");
}
}

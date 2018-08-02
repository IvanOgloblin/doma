#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
int fd;
if((fd=open("fifo1", 0666)) == - 1)
{
    fprintf(stderr, "Невозможно открыть fifo\n");
    exit(0);
}
printf(" CHILD: Мой PID -- %d\n", getpid());
char resstring[14];
if(read(fd, resstring, 14) < 0)
{
    printf("Can\'t read string\n"); 
    exit(-1); 
}
printf(" CHILD: Принятая строка -- %s\n", resstring);
printf(" CHILD: Выход");
exit(0);
}

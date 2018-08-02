#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd;
    //if((mkfifo("fifo1", 0666)) == -1)
    //{
//	fprintf(stderr, "Невозможно создать fifo\n");
//        exit(0);
//    }
    if((fd=open("fifo1", 0666)) == - 1)
    {
	fprintf(stderr, "Невозможно открыть fifo\n");
        exit(0);
    }
    printf("PARENT: Мой PID -- %d\n", getpid());
    char string[] = "Hello, world!";
    if(write(fd, string, sizeof(string)) != 14)
    {
	printf("Can\'t write all string\n"); 
	exit(-1); 
    }
    printf("PARENT: Отправленая строка -- %s\n", string);
    printf("PARENT: Выход!\n");
}

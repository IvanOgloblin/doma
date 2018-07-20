#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
int rp3;
int rp2;
int rp4;
int rp5;
int rp6;
pid_t pid3;
int rv3;
switch(pid3=fork()) {
case -1:
perror("fork"); /* произошла ошибка */
exit(1); /*выход из родительского процесса*/
case 0:
printf(" CHILD3: Мой PID -- %d\n", getpid());
printf(" CHILD3: PID моего родителя -- %d\n",getppid());
    int rp4;
    int rp5;
    pid_t pid4;
    int rv4;
    switch(pid4=fork()) {
    case -1:
    perror("fork"); /* произошла ошибка */
    exit(1); /*выход из родительского процесса*/
    case 0:
    printf(" CHILD4: Мой PID -- %d\n", getpid());
    printf(" CHILD4: PID моего родителя -- %d\n",getppid());
    exit(rv4);
    default:
    printf("PARENT3: Мой PID -- %d\n", getpid());
    printf("PARENT3: PID моего потомка %d\n",pid4);
    
	pid_t pid5;
	int rv5;
	switch(pid5=fork()) {
	case -1:
	perror("fork"); /* произошла ошибка */
	exit(1); /*выход из родительского процесса*/
	case 0:
	printf(" CHILD5: Мой PID -- %d\n", getpid());
	printf(" CHILD5: PID моего родителя -- %d\n",getppid());
	exit(rv5);
	default:
	printf("PARENT3: PID моего потомка %d\n",pid5);
    
	printf("PARENT3: Я жду, пока потомок 5 не вызовет exit()...\n");
	waitpid(pid5,rp5,0);
	}
    
    printf("PARENT3: Я жду, пока потомок 4 не вызовет exit()...\n");
    waitpid(pid4,rp4,0);
    exit(rv3);
    }
default:
printf("PARENT1: Мой PID -- %d\n", getpid());
printf("PARENT1: PID моего потомка %d\n",pid3);


pid_t pid2;
int rv2;
switch(pid2=fork()) {
case -1:
perror("fork"); /* произошла ошибка */
exit(1); /*выход из родительского процесса*/
case 0:
printf(" CHILD2: Мой PID -- %d\n", getpid());
printf(" CHILD2: PID моего родителя -- %d\n",getppid());
	pid_t pid6;
	int rv6;
	switch(pid6=fork()) {
	case -1:
	perror("fork"); /* произошла ошибка */
	exit(1); /*выход из родительского процесса*/
	case 0:
	printf(" CHILD6: Мой PID -- %d\n", getpid());
	printf(" CHILD6: PID моего родителя -- %d\n",getppid());
	exit(rv6);
	default:
	printf("PARENT2: PID моего потомка %d\n",pid6);
	printf("PARENT2: Я жду, пока потомок 5 не вызовет exit()...\n");
	waitpid(pid6,rp6,0);
	}

exit(rv2);
default:
printf("PARENT1: PID моего потомка %d\n",pid2);
printf("PARENT1: Я жду, пока потомок 2 не вызовет exit()...\n");
waitpid(pid2,rp2,0);
}

printf("PARENT1: Я жду, пока потомок 3 не вызовет exit()...\n");
waitpid(pid3,rp3,0);
//printf("PARENT1: Код возврата потомка:%d\n",WEXITSTATUS(rv));
printf("PARENT1: Выход!\n");
}
}
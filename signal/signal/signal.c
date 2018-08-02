#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void fn(int sig)
{
    printf("Сигнал терм принят");
    exit(0);
}

int main()
{
    void (*fptr)(int);
    fptr=signal(SIGTERM,fn);
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");
    while(1)
    {
    }
    exit(0);
}
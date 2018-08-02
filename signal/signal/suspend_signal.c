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
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGHUP);
    sigprocmask(SIG_BLOCK, &set, 0);
    fptr=signal(SIGTERM,fn);
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");
    sigsuspend(&set);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void term_handler(int i) // функция-обработчик сигнала
{ 
    printf ("Сигнал принят, завершаюсь\n");
    exit(0);
}
int main(int argc, char ** argv) 
{
    struct sigaction sa; /* спец. структура используемая в качестве параметра системного вызова sigaction() */
    sigset_t newset; // набор сигналов
    sigemptyset(&newset); // инициализирует набор сигналов, указанный в newset, и "очищает" его от всех сигналов
    sigaddset(&newset, SIGHUP); // добавляем сигнал SIGHUP в наш набор  
    sigprocmask(SIG_BLOCK, &newset, 0); // добавляем набор newset в группу заблокированных 
    sa.sa_handler = term_handler; // добавляем в структуру типа  sigaction указатель на функцию обработчик сигнала
    sigaction(SIGTERM, &sa, 0);  
    printf("My pid is %i\n", getpid()); // выводим pid процесса
    printf("Waiting...\n");
    sigsuspend(&newset);
    exit(1);
}
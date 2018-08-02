#include<stdio.h>  // Для printf
#include<string.h> // Для strtok

int main(void)
{    
    int fdo;
    if(pipe(&fdo) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    int ex=0;
    char *str;
//    while(!ex)
//    {
	printf("Inter comand: ");
        //scanf("%s",str);
        gets(str);
                            
    // Набор символов, которые должны входить в искомый сегмент
    char sep [1]="|";
    // Переменная, в которую будут заноситься начальные адреса частей
    // строки str
    char *istr;
    printf ("Исходная строка: %s\n", str);
    printf ("Результат разбиения:\n");
    // Выделение первой части строки
    istr = strtok (str,sep);
    // Выделение последующих частей
    while (istr != NULL)
    {
	// Вывод очередной выделенной части
        printf ("%s\n",istr);
        // Выделение очередной части строки
        istr = strtok (NULL,sep);
    }
    
        
        
        
    return 0;
}
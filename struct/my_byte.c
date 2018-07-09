#include <stdio.h>
struct my_byte
{
    char letter1:8;
    int number1:4;
    char letter2:8;
    int number2:4;
};

int main()
{
    char word[10]={'A',0,0,0,0,'B',0,0,0,0};
    struct my_byte byteword;
    struct my_byte *ptr=&byteword;
    char *ptrL=word;
    int *ptrN=word;
    ptrN+=sizeof(char);
    ptr->letter1=*ptrL;
    ptr->number2=*ptrN;
    ptrL+=sizeof(char)+sizeof(int);
    ptr->letter2=*ptrL;
    ptrN+=sizeof(char)+sizeof(int);
    ptr->number2=*ptrN;
    printf("Letter:%c Number:%d Letter:%c Number:%d",ptr->letter1,ptr->number1,ptr->letter2,ptr->number2);
    return 0;
}
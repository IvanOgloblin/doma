#include<stdio.h>
#define N 11
int main()
{
    short mass[N];
    short i=0;
    for(i=0;i<N;i++)
    {
	mass[i]=i;
    }
    
    for(i=0;i<N;i++)
    {
	printf("%d\t",mass[i]);
    }
    
    printf("\n");
    short c=N/2;
    for(i=0;i<c;i++)
    {
	short buff=mass[i];
	mass[i]=mass[N-i-1];
	mass[N-i-1]=buff;
	short g=0;
	//    for(g=0;g<N;g++)
	//{
	//    printf("%d\t",mass[g]);
	//}
	//printf("\n");
    }
    
     for(i=0;i<N;i++)
    {
	printf("%d\t",mass[i]);
    }
    
    return 0;
}
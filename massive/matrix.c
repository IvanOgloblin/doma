#include<stdio.h>
#define N 6
int main()
{
    short mass[N][N];
    short i=0;
    short add=0;
    short count =0;
    while(count<=N*N)
    {
	for(i=add;i<N-add;i++)//вправо
	{
	    //if(i>4||i<0){printf("%d r",i);count++;return 0;}
	    mass[i][add]=count;
	    //printf("r %d  \t",count);
	    count++;
	    
	}
	if(count>=N*N)break;
	
	for(i=1+add;i<N-add;i++)//вниз
	{
	    //if(i>4||i<0){printf("%d d %d",i,add);count++;return 0;}
	    mass[N-add-1][i]=count;
	    //printf("d %d  \t",count);
	    count++;
	}
	if(count>=N*N)break;
	
	for(i=N-add-2;i>=add;i--)//влево
	{
	    //if(i>4||i<0){printf("%d l",i);count++;return 0;}
	    mass[i][N-add-1]=count;
	    //printf("l %d  \t",count);
	    count++;
	    
	}
	if(count>=N*N)break;
	
	for(i=N-2-add;i>add;i--)//вверх
	{
	    //if(i>4||i<0){printf("%d u",i);count++;return 0;}
	    mass[add][i]=count;
	    //printf("u %d  \t",count);
	    count++;
	}
	if(count>=N*N)break;
	add++;
	//printf("%d \t %d \n",add,count);
    }
    
     for(i=0;i<N;i++)
    {
	int g=0;
	for(g=0;g<N;g++)
	{
	    printf("%d\t",mass[g][i]);
	}
	printf("\n");
    }
    
    return 0;
}
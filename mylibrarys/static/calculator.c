#include<stdio.h>
extern float add(float a,float b);
extern float div(float a,float b);
extern float mul(float a,float b);
extern float rem(float a,float b);
int main()
{
    float num=0;
    printf("Your number: %f\n",num);
    int flag;
    printf("1.Add\n");
    printf("2.Remove\n");
    printf("3.Multiply\n");
    printf("4.Divide\n");
    printf("5.Exit\n");
    scanf("%d",&flag);
    while(flag!=5)
    {
	switch(flag)
	{
	    case 1:{
		float alter;
		scanf("%f",&alter);
		num=add(num,alter);
		break;}
	    case 2:{
		float alter;
		scanf("%f",&alter);
		num=rem(num,alter);
		break;}
	    case 3:{
		float alter;
		scanf("%f",&alter);
		num=mul(num,alter);
		break;}
	    case 4:{
		float alter;
		scanf("%f",&alter);
		num=div(num,alter);
		break;}
	    case 5:{
		return 0;
		break;}
	    default:
		break;
	}
	printf("Your number: %f",num);
	printf("1.Add\n");
	printf("2.Remove\n");
	printf("3.Multiply\n");
	printf("4.Divide\n");
	printf("5.Exit\n");
	scanf("%d",&flag);
    }
    return 0;
}
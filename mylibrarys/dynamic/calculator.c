#include<stdio.h>
#include<stddef.h>
#include<dlfcn.h>
#include<stdlib.h>
int main()
{
    char (*lib)[][4];
    lib = (char (*)[][4])malloc(100);
    void *libs[4];
    int countoflib=0;
    printf("Inter count of Librarys: ");
    scanf("%d",&countoflib);
    int i=0;
    while(i<countoflib)
    {
	printf("Inter Library`s path: ");
	scanf("%s",((*lib)[i]));
//	libs[i] = dlopen(((*lib)[i]),RTLD_LAZY);
	libs[i] = dlopen(((*lib)[i]),RTLD_LAZY);
	if (!libs[i])
	{
	    return 1;
	}
	char *Name=dlsym(libs[i],"Name");
	printf("%d) %s\n,",i,Name);
	i++;
    }
    float num=0;
    printf("Your number: %f\n",num);
    int flag;
    printf("1.Add\n");
    printf("2.Remove\n");
    printf("3.Multiply\n");
    printf("4.Divide\n");
    printf("5.Exit\n");
    scanf("%d",&flag);/*
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
    }*/
    return 0;
}
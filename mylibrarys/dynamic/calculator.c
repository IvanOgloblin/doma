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
	libs[i] = dlopen(((*lib)[i]),RTLD_LAZY);
	if (!libs[i])
	{
	    return 1;
	}
	i++;
    }
    i=0;
    float (*func[4])(float,float);
    while(i<countoflib)
    {
	char *Name=dlsym(libs[i],"Name");
	func[i]=dlsym(libs[i],"glob");
	printf("%d) %s\n",i,Name);
	i++;
    }
    printf("%d) Exit\n",i);
    float num=0;
    printf("Your number: %f\n",num);
    int f;
    printf("aaaabbbbb\n");
    printf("gggs\n");
    scanf("%d",&f);
    printf("%d",f);
    while(f<=countoflib+1&&f>=0)
    { printf("br1");
	float alter=1;
	printf("br2");
	printf("Inter number:");
	scanf("%f",&alter);
	printf("%f",alter);
	printf("break1");
	num=func[f](num,alter);
	while(i<countoflib)
	{
	    char *Name=dlsym(libs[i],"Name");
	    func[i]=dlsym(libs[i],"glob");
	    printf("%d) %s\n",i,Name);
	    i++;
	}
	printf("%d) Exit\n",i);
        printf("Your number: %f\n",num);
	//int flag=0;    
	
	scanf("%d",&f);
	/*switch(flag)
	{
	    case :{
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
	scanf("%d",&flag);*/
    }
    return 0;
}
#include <stdio.h>
struct mycomplex
{
    float Re;
    float Im;
};

int main()
{
    struct mycomplex MCX;
    struct mycomplex *ptr=&MCX;
    int flag;
    float InRe;
    float InIm;
    float buffer;
    ptr->Im=0;
    ptr->Re=0;


    printf("1.add\n");
    printf("2.sub\n");
    printf("3.mul\n");
    printf("4.div\n");
    printf("5.exit\n");
    scanf("%d",&flag);
    while(flag!=5)
    {
	switch(flag)
	{
	    case 1:
		printf("Inter Re:");
		scanf("%f",&InRe);
		printf("Inter Im:");
		scanf("%f",&InIm);
		ptr->Re+=InRe;
		ptr->Im+=InIm;
		break;
	    case 2:
		printf("Inter Re:");
		scanf("%f",&InRe);
		printf("Inter Im:");
		scanf("%f",&InIm);
		ptr->Re-=InRe;
		ptr->Im-=InIm;
		break;
	    case 3:
		printf("Inter Re:");
		scanf("%f",&InRe);
		printf("Inter Im:");
		scanf("%f",&InIm);
		buffer=ptr->Re;
		ptr->Re=ptr->Re*InRe-ptr->Im*InIm;
		ptr->Im=buffer*InIm+ptr->Im*InRe;
		break;
	    case 4:
		printf("Inter Re:");
		scanf("%f",&InRe);
		printf("Inter Im:");
		scanf("%f",&InIm);
		buffer=ptr->Re;
		ptr->Re=ptr->Re*InRe-ptr->Im*(-InIm);
		ptr->Im=buffer*(-InIm)+ptr->Im*InRe;
		ptr->Re=ptr->Re/(InRe*InRe-(-InIm*InIm));
		ptr->Im=ptr->Im/(InRe*InRe-(-InIm*InIm));
		break;
	    case 5:
		printf("END");
		break;
	    default:
		break;
	}
	printf("Result: %f + i%f\n\n",ptr->Re,ptr->Im);
	printf("1.add\n");
	printf("2.sub\n");
	printf("3.mul\n");
	printf("4.div\n");
	printf("5.exit\n");
	scanf("%d",&flag);
    }
    return 0;
}
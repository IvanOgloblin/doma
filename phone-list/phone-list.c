#include<stdio.h>
#include<malloc.h>
#include<stddef.h>
//struct pl;
typedef struct pl
{
    char *Name;
    char *Sname;
    int number;
    struct pl *Next;
}phlist;

struct pl *make_new_list()
{
    struct pl *buffer;
    buffer->Next=NULL;
    return buffer;
}

int streq(char *str1, char *str2)
{
    if(sizeof(str1)!=sizeof(str2))
    return 0;
    int count=sizeof(str1);
    int i;
    for(i=0;i<count;i++)
    {
	if(str1[i]!=str2[i])
	return 0;
    }
    return 1;
}

int main()
{
    int flag;
    struct pl buffer;
    struct pl *root;
    struct pl *ptr;
    ptr=NULL;
    root=NULL;
    printf("1.Add\n");
    printf("2.Dell\n");
    printf("3.Search\n");
    printf("4.List\n");
    printf("5.Exit\n");
    scanf("%d",&flag);
    while(flag!=5)
    {
	switch(flag)
	{
	    case 1:
		if(root==NULL)
		{
		    root=malloc(sizeof(phlist));
		    //root=make_new_list();
		    root=malloc(sizeof(phlist));
		    root->Name=malloc(sizeof(char)*40);
		    printf("Inter Name:");
		    scanf("%s",root->Name);
//		    fgets(root->Name,40,stdin);
		    root->Sname=malloc(sizeof(char)*60);
		    printf("Inter Surname:");
		    scanf("%s",root->Sname);
//		    fgets(root->Sname,60,stdin);
		    printf("Inter number:");
		    scanf("%d",&root->number);
		    ptr=root;
		}
		else
		{
		    ptr->Next=malloc(sizeof(phlist));
		    ptr=ptr->Next;
		    ptr->Name=malloc(sizeof(char)*40);
		    printf("Inter Name:");
		    scanf("%s",ptr->Name);
		    ptr->Sname=malloc(sizeof(char)*60);
		    printf("Inter Surname:");
		    scanf("%s",ptr->Sname);
		    printf("Inter number:");
		    scanf("%d",&ptr->number);
		    ptr->Next=NULL;
		}		
		break;
	    case 2:
		printf("1.Remove for Name/Surname\n");
		printf("2.Remove phone number\n");
		scanf("%d",&flag);
		switch(flag)
		{
		    case 1:
			{
			struct pl *last;
			last=NULL;
			char *Name;
			Name=malloc(sizeof(char)*40);
			char *Sname;
			Sname=malloc(sizeof(char)*60);
			printf("Inter Name: ");
			scanf("%s",Name);
			printf("Inter Surname: ");
			scanf("%s",Sname);
			ptr=root;
			while(root!=NULL)
			{
			    if(streq(ptr->Name,Name)==1&&streq(ptr->Sname,Name)==1)
				{
				    if(ptr->Next!=NULL)
				    {	
					root=ptr->Next;free(ptr);ptr=root;
				    }
				    else 
				    {
					free(ptr);
					ptr=NULL;
					root=NULL;
					break;
				    }
				}
			    else
				{last=root;ptr=ptr->Next;break;}
			}
			while(ptr!=NULL)
			{
			    struct pl *buffer;
			    if(streq(ptr->Name,Name)==1&&streq(ptr->Sname,Sname)==1)
			    {
				if(ptr->Next!=NULL)
				    {buffer=ptr;ptr=ptr->Next;last->Next=ptr;free(buffer);}
				else
				{
				    buffer=ptr;
				    last->Next=ptr->Next;
				    ptr=last;
				    free(buffer);
				    break;
				}
			    }
			    else {last=ptr;ptr=ptr->Next;}
			}
			ptr=root;
			if(ptr!=NULL)
			while(ptr->Next!=NULL)
			{ptr=ptr->Next;}
			break;
			
			case 2:
			    {
			    struct pl *last;
			    last=NULL;
			    int num;
			    printf("Inter Number: ");
			    scanf("%d",&num);
			    ptr=root;
			    while(root!=NULL)
			    {
				if(ptr->number==num)
				    {
					if(ptr->Next!=NULL)
					{	
					    root=ptr->Next;free(ptr);ptr=root;
					}
					else {ptr=NULL;root=NULL;}
				    }
				else
				    {last=root;ptr=ptr->Next;break;}
			    }
			    while(ptr!=NULL)
			    {
				struct pl *buffer;
				if(ptr->number==num)
				    {
				    if(ptr->Next!=NULL)
					{buffer=ptr;ptr=ptr->Next;last->Next=ptr;free(buffer);}
					else
					{
					    buffer=ptr;
					    last->Next=ptr->Next;
					    ptr=last;
					    free(buffer);
					    break;
					}
				    }
				else {last=ptr;ptr=ptr->Next;}
			    }
			    break;
			    }
			}
		}
		break;
	    case 3:
	    {
		printf("1.Search for Name/Surname\n");
		printf("2.Search phone number\n");
		scanf("%d",&flag);
		switch(flag)
		{
		    case 1:
		    {
			char *Name;
			Name=malloc(sizeof(char)*40);
			char *Sname;
			Sname=malloc(sizeof(char)*60);
			printf("Inter Name: ");
			scanf("%s",Name);
			printf("Inter Surname: ");
			scanf("%s",Sname);
			ptr=root;
			int count=1;
			while(ptr!=NULL)
			{
			    if(streq(ptr->Name,Name)==1&&streq(ptr->Sname,Sname)==1)
				printf("%d)Name: %s, Surname: %s, Number: %d \n",count,ptr->Name,ptr->Sname,ptr->number);
				ptr=ptr->Next;
				count++;
			}
			ptr=root;
			if(ptr!=NULL)
			while(ptr->Next!=NULL)
			{ptr=ptr->Next;}
			break;
		    }
		    case 2:
		    {
			int num;
			printf("Inter Number: ");
			scanf("%d",&num);
			ptr=root;
			int count=1;
			while(ptr!=NULL)
			{
			    if(num==ptr->number)
				printf("%d)Name: %s, Surname: %s, Number: %d \n",count,ptr->Name,ptr->Sname,ptr->number);
				ptr=ptr->Next;
				count++;
			}
			ptr=root;
			if(ptr!=NULL)
			while(ptr->Next!=NULL)
			{ptr=ptr->Next;}
			break;
		    }
		}
		break;
	    }
	    case 4:
		ptr=root;
		int count=1;
		while(ptr!=NULL)
		{
		    printf("%d)Name: %s, Surname: %s, Number: %d \n",count,ptr->Name,ptr->Sname,ptr->number);
		    ptr=ptr->Next;
		    count++;
		}
		ptr=root;
		while(ptr->Next!=NULL)
		{ptr=ptr->Next;}
	        break;
	}
	printf("\n\n1.Add\n");
	printf("2.Dell\n");
	printf("3.Search\n");
	printf("4.List\n");
	printf("5.Exit\n");
	scanf("%d",&flag);
    }
    return 0;
}
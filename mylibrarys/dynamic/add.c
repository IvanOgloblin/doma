float add(float a, float b)
{
    return a+b;
}
float (*glob)(float,float)=add;
char Name[10]="Add";
float mul(float a, float b)
{
    return a*b;
}
float (*glob)(float,float)=mul;
char Name[10]="Multiply";
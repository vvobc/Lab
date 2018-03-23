#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#define MAXBITS 64 //B edit
int main()
{
    double DecimalPoint,Buff;
    int i,j,Expo,Decimal,DataBuff[MAXBITS],Output[MAXBITS];
    char ch;
    while(scanf("%lf%c",&Buff,&ch)!=2||ch!='\n')    //>>>>> Input real numbers
        rewind(stdin);
    if(Buff>=0)                                     //>>>>> 0 Positive numbers
        Output[0]=0;
    else
    {
        Output[0]=1;                                //>>>>> 1 Negative numbers
        Buff*=-1;
    }
    Decimal=Buff;                                   //>>>>> Decimal is integer
    DecimalPoint=Buff-Decimal;                      //>>>>> DecimalPoint is Decimal Point
    if(Decimal>0)
    {
        for(i=MAXBITS-1;i>=0;i--)                   //>>>>> Converter Decimal to Binary (integer)
        {
            DataBuff[i]=Decimal%2;
            Decimal/=2;
        }
        for(i=0;DataBuff[i]!=1;i++){}               //>>>>> Move points
        Expo=MAXBITS-i+1022;
        for(j=11;j>=1;j--)                          //>>>>> Converter Decimal to Binary (Exponent)
        {
            Output[j]=Expo%2;
            Expo/=2;
        }
        for(j=12,i=i+1;i<MAXBITS;i++,j++)           //>>>>> Copy Binary (Decimal Point) into Output *Start index at 12
           Output[j]=DataBuff[i];
        for(j=j;j<MAXBITS;j++)                      //>>>>> Converter Decimal to Binary (Decimal Point)
        {
            DecimalPoint*=2;
            if(DecimalPoint>=1)
            {
                Output[j]=1;
                DecimalPoint-=1;
            }
            else
                Output[j]=0;
        }
    }
    else
    {
        for(i=0;i<MAXBITS;i++)                      //>>>>> Converter Decimal to Binary (Decimal Point)
        {
            DecimalPoint*=2;
            if(DecimalPoint>=1)
            {
                DataBuff[i]=1;
                DecimalPoint-=1;
            }
            else
                DataBuff[i]=0;
        }
        for(i=0;DataBuff[i]!=1;i++){}               //>>>>> Move points
        Expo=1022-i;
        for(j=11;j>=1;j--)                          //>>>>> Converter Decimal to Binary (Exponent)
        {
            Output[j]=Expo%2;
            Expo/=2;
        }
        for(j=12,i=i+1;j<MAXBITS;i++,j++)           //>>>>> Copy Binary (Decimal Point) into Output *Start index at 12
        {
            if(i<MAXBITS)
                Output[j]=DataBuff[i];
            else
                Output[j]=0;
        }
    }
    //printf("Sign        Exponent          Mantissa\n\n");
    printf("%d           ",Output[0]); //print Sign
    for(i=1;i<4;i++)
        printf("%d",Output[i]); //print Exponent
    for(i=4;i<12;i++)
    {
        if(i%4==0)
            printf(" ");
        printf("%d",Output[i]); //print Exponent
    }
    printf("    ");
    for(i=12;i<MAXBITS;i++)
    {
        if(i%4==0)
            printf(" ");
        printf("%d",Output[i]);   //print Mantissa
    }
    printf("\n");

    int y,Ten=0;
    for(y=0,i=11;i>=1;i--,y++)
    {
        Ten+=Output[i]*(int)pow(2,y); //>>>>> Converter Binary to Decimal (Exponent)
    }
    Ten-=1023;
    if(Ten<=0)
    {
        if(Output[0]==1)
            printf("-0.");
        else
            printf("0.");
        Ten*=-1;
        for(i=1;i<Ten;i++)
            printf("0");
        printf("1");
        for(i=i;i<MAXBITS;i++)
            printf("%d",Output[i]);
        printf("\n0\n0");
    }
    else
    {
        if(Output[0]==1)
            printf("-1");
        else
            printf("1");
        for(i=12;i<12+Ten;i++)
            printf("%d",Output[i]);
        printf(".");
        for(i=i;i<MAXBITS;i++)
            printf("%d",Output[i]);
        printf("\n1");
        for(i=12;i<12+Ten;i++)
            printf("%d",Output[i]);
        int Number=0;
        for(y=0,i=11+Ten;i>=12;i--,y++)
        {
            Number+=Output[i]*(int)pow(2,y);
        }
        Number+=1*(int)pow(2,y);
        if(Output[0]==1)
            Number*=-1;
        printf("\n%d",Number);
    }
    //printf("\n\n1 Bit       11 Bits           52 Bits\n\n");
    //main();
    return 0;
}

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#define MAX 128
int Binary(int data[],char text[])//asdfghkl;
{
    int x,i;
    char str[500];
    do
    {
        x=0;
        printf("%s ",text);
        scanf("%s",str);
        if(strlen(str)>8)                                           //>>>    Check number not more 8 bits
            x=1;                                                    //>>>    x=1 More than 8 bits
        else
        {
            for(i=0;i<strlen(str);i++)                              //\*
            {                                                       // \*    Move data(char) into data(int)
                data[i+(MAX-strlen(str))]=(str[i]-48);              //  \*   and Check number is 0 1 only
                if(str[i]!='0'&&str[i]!='1')                        //  /    x=2 not only 0 1
                    x=2;                                            // /
            }                                                       ///
        }
        if(x==1)
            printf("More than 8 bits \n");
        else if(x==2)
            printf("Use only binary numeral system ( 0 1 )\n");
    }while(x!=0);
}
int plus(int data1[],int data2[],int output[],int buff[])
{
 int i,y=0;                                         // First carry bit =0 (y=0)
    buff[MAX-1]=0;                                  // Function + Binary number
    for(i=MAX-1;i>=0;i--)                           // y is carry bit,
    {                                               // y=0 Binary number = 0
        y+=(data1[i]+data2[i]);                     // y=1 Binary number = 1
        if(y>1)                                     // y=2 Binary number = 0
        {                                           // y=3 Binary number = 1
            if(y==2)                                // if y>1 set new carry bit = 1
                output[i]=0;
            else
                output[i]=1;
            y=buff[i-1]=1;
        }
        else
        {
            if(y==0)
                output[i]=0;
            else
                output[i]=1;
            y=buff[i-1]=0;
        }
    }
}
int OneComp(int data[])
{
    int i;
    for(i=0;i<MAX;i++)
        data[i] = (data[i]==1)? 0:1;                            //>>>  switching 0 <-> 1
}
int Show(int data[])
{
    int Ten=0,i,y;
    for(i=0;i<MAX;i++)
        printf("%d",data[i]);                                   // Print Binary number
    for(y=MAX-1,i=0;i<MAX;i++,y--)                              // and number base 10
    {                                                           //
        Ten+=data[i]*(int)pow(2,y);                             // Calculations Number base 10
    }
    if(data[0]==1)                                              //
        Ten-=256;                                               //
    printf("   (%d)",Ten);                                      //
    printf("\n");                                               //
}
int main()
{
    int i,DATA[MAX]={0,0,0,0,0,0,0,0},DATA2[MAX]={0,0,0,0,0,0,0,0};
    int OUTPUT[MAX]={0,0,0,0,0,0,0,0},BUFF[MAX],ONE[MAX]={0,0,0,0,0,0,0,1};
    char op,ch;
    Binary(DATA,"First");                                           //>>>> Input First binary number

    printf("Enter Operators + or - only ");                         //\*
    while(scanf(" %c%c",&op,&ch)!=2||(op!='+'&&op!='-')||ch!='\n')  // \*
    {                                                               //  \*   Input Operator , + - only
        printf(" + or - Only\n");                                   //  /    Defense input values other
        rewind(stdin);                                              // /
    }                                                               ///

    Binary(DATA2,"Second");                                         //>>>> Input Second binary number

    if(op=='-')                                                     //\*    Function OneComp (1's Complement)
    {                                                               // \*    is change 1 -> 0, 0 -> 1
        OneComp(DATA2);                                             //  \*
        plus(DATA2,ONE,OUTPUT,BUFF);                                //   \*   Function Plus is 1's Complement + 1 or 2's Complement
        for(i=0;i<MAX;i++)                                          //   /
            DATA2[i]=OUTPUT[i];                                     //  /
    }                                                               ///

    plus(DATA,DATA2,OUTPUT,BUFF);                                   //>>>>  First Number + Second Number

    //system("cls");                                                  //>>>>  Clear screen

    for(i=0;i<MAX;i++)                                              //\*
    {                                                               // \*
        if(BUFF[i]==1)                                              //  \*
            printf("%d",BUFF[i]);                                   //      Show carry bit
        else                                                        //  /
            printf(" ");                                            // /
    }                                                               ///
    printf("\n");
    Show(DATA);                                                     //>>>>  Show Number(1) ex. 1010 (10)
    printf("         +\n");
    Show(DATA2);                                                    //>>>>  Show Number(2) ex. 1010 (10)
    printf("--------\n");
    if((DATA[0]==DATA2[0]&&((DATA[0]==0&&OUTPUT[0]==0)||(DATA[0]==1&&OUTPUT[0]==1)))||DATA[0]!=DATA2[0])  //>>>> If the first(index[0]) is equal to zero. Value is positive only ถ้าตัวแรกของเลขเป็นเลข0 เลขฐาน2 มีค่าอยู่ในโซนบวก
        Show(OUTPUT);//>>>>  Show Answer ex. 1010 (10)                                                    //>>>> If the first(index[0]) is equal to one . Value is Negative only ถ้าตัวแรกของเลขเป็นเลข1 เลขฐาน2 มีค่าอยู่ในโซนลบ
    else                                                                                                  //>>>> So positive(DATA) + positive(DATA2) Must equal positive only    จำนวนบวก+จำนวนบวกจะได้จำนวนบวก
        printf("Overflow\n");                                                                             //>>>> And Negative + Negative Must= Negative only                     จำนวนลบ+จำนวนลบจะได้จำนวนลบ
    printf("========\n");                                                                                 //o>>> if positive+positive!=positive or Negative + Negative != Negative ,then Overflow ถ้าไม่เป็นตามนั้น แปลว่าเกิดการ  Overflow
}

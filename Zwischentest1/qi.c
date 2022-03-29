#include <stdio.h>
#include <stdlib.h>

int main()
{
    int Number1,Number2,Result = 0,remainder;
    char Oper,Option = '\0';
    float m;
    int p=0,n=0;
    printf("\n");
    printf("Number: ");
    scanf("%d",&Number1);
    printf("\n");
    do{
        printf("Operator: ");
        scanf("%s",&Oper);
        printf("\n");
        if(Oper=='='){
            break;
        }
        else if((Oper!='+')&&(Oper!='-')&&(Oper!='*')&&(Oper!='/')){
            printf("Unknown operator.\n");
        continue;
        }
        else
        printf("Number: ");
        scanf("%d",&Number2);
        printf("\n");
        if (Oper=='+'){
            Result=Number1+Number2;
            Number1=Result;
            printf("Result: %d\n",Number1);
        }
        else if(Oper=='-'){
            Result=Number1-Number2;
            Number1=Result;
            printf("Result: %d\n",Number1);
        }
        else if(Oper=='*'){
            Result=Number1*Number2;
            Number1=Result;
            printf("Result: %d\n",Number1);
        }
        else if((Oper=='/') && (Number2==0)){
            printf("Division by 0.\n");
            printf("No new result.\n");
        }
        else if((Oper=='/') && (Number2!=0)){
            remainder=Number1%Number2;

            if(remainder==0){
                Result=Number1/Number2;
                Number1=Result;
                printf("Result: %d\n",Number1);
            }
            else if(remainder!=0){
                printf("Division has remainder %d. Round (r), cut off (c), or discard (d)?",remainder);
                printf("\n");
                printf("Option: ");
                scanf("%s",&Option);
                printf("\n");
                if(Option=='r'){
                    remainder=abs(remainder);
                    Result=(Number1-remainder)/Number2;
                    m=(float)Number1/Number2;
                    m=m-Result;
                    if(m>=0.5){
                        Result=Result+1;
                    }else{
                    Result=Result;
                    }
                    Number1=Result;
                    printf("Result: %d\n", Result);
                }
                else if(Option=='c'){
                    Result=(Number1-remainder)/Number2;
                    Number1=Result;
                    printf("Result: %d\n",Number1);
                }
                else if(Option=='d'){
                    printf("No new result.\n");
                }
                else {
                    while((Option!='r')&&(Option!='c')&&(Option!='d')){
                        printf("Unknown option.\n");
                        printf("Option: ");
                        scanf("%s",&Option);
                        printf("\n");
                        if(Option=='r'){
                            remainder=abs(remainder);
                            Result=(Number1-remainder)/Number2;
                            m=(float)Number1/Number2;
                            m=m-Result;
                            if(m>=0.5){
                                Result=Result+1;
                            }else{
                                Result=Result;
                            }
                        Number1=Result;
                        printf("Result: %d\n", Result);
                        }
                else if(Option=='c'){
                    Result=(Number1-remainder)/Number2;
                    Number1=Result;
                    printf("Result: %d\n",Number1);
                }
                else if(Option=='d'){
                    printf("No new result.\n");
                }
                    }
                }
            }
        }
        if(Result<0){
            if(((Oper=='/')&&(Number2==0))||(Option=='d'))
                n=n;
                else
                n++;
        }
        else if(Result>=0){
            if(((Oper=='/')&&(Number2==0))||(Option=='d'))
                p=p;
            else
                p++;
        }
    }while(Oper!='=');
    printf("Final result: %d\n",Number1);
    printf("Number of positive: %d\n",p);
    printf("Number of negative: %d\n",n);
    return 0;
}

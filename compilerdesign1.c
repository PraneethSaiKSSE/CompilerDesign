#include<stdio.h>
int main()
{
    char str[30];
    int i = 2, a = 0;
    printf("\nWrite a C Program to Identify Whether a Given Line is a Commentor Not.");
    printf("\n\nEnter Text : ");
    scanf("%s",str);
    if(str[0] == '/')
    {
        if(str[1] == '/') {
            printf("\nIt is a single line  Comment.");
        } 
        else if(str[1] == '*') 
        {
            for(i = 2; i <= 30; i++)
            {
                if(str[i] == '*' && str[i + 1] == '/')
                {
                    a = 1;
                    break;
                }
                else {
                    continue;
                }
            }
            if(a == 0)
            {
                printf("\nIt is Not a Comment.");
            }
            else
            {
                printf("\nIt is  a multiple line  Comment.");
            }
        }
    }
    else
    {
        printf("\nIt is Not a Comment.");
    }
    return 0;
}
        

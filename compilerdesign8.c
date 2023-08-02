#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main(){
char a[100];
int i;
printf("enter the string");
scanf("%s",&a);
int l=strlen(a);
for(i=0;i<l;i++){
	if(isalpha(a[i]))
	{
		printf("%c is identifier\n",a[i]);
	}
	else if(isdigit(a[i]))
	{
		printf("%c is digit\n",a[i]);
	}
	else
	{
		printf("%c is operator\n",a[i]);
	}
}
}

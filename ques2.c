#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int main()
{
int c,i,j,n,k,y,z;
printf("Enter length of page reference string:\n");
scanf("%d",&n);
int ref_string[n];
int Frame[n];
for(i=0;i<=n;i++)
{
	ref_string[i] = rand()%10;
	printf("%d  ",ref_string[i]);
}
printf("\n");
for(z=1;z<=7;z++) 
{
c=0;
for(i=0;i<z;i++)
Frame[i]= -1; 
j=0;
printf("ref_string \t page_frames\n");
for(i=0;i<n;i++)
{	
printf("%d   \t  \t",ref_string[i]);
y=0;
for(k=0;k<z;k++)
if(Frame[k]==ref_string[i])
y=1;
if (y==0)
{	
Frame[j]=ref_string[i];
j=(j+1)%z;
c++;
for(k=0;k<z;k++)
printf("%d\t",Frame[k]);
}
printf("\n");
}
printf("Page_Fault - %d \n",c);
}
return 0;
}

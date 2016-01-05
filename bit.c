#include<stdio.h>
#include<string.h>

int main(void)
{
    int entry=0;
    
    scanf("%d",&entry);
    
	switch(entry)
	{
	 case 1 :  // reverse n bit @ bit p
			{
			 int num =0x55;
			 #define SET_BITS(p,n)  ((1<<n)-1<<p)   //ËãÊõ>ÒÆÎ» 
			 #define REVERSE_BITS(num,p,n)  (num ^= SET_BITS(p,n))
			 REVERSE_BITS(num,p,n);
			 printf("%x\n",num) ;
			 } 
			 break;
		default:
			break;	
	} 

	return 0;
}

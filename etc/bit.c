#include<stdio.h>
#include<stdlib.h>

int count_bit(int num)
{
	int n=0;

	while(num) {
		num &= (num-1);
		n++;
	}
	printf("Total %d bit\n",n);
}


int main()
{
	int cmd = 0;

	printf("input a cmd:");

	while(scanf("%d",&cmd) != EOF) {


		switch(cmd)	{
			case 1: {
				int num;
				/* input:-1 output:32
					     -2         31
					result: negative number in RAM store in 2's complement
				 */
				printf("input a number:"); 
				scanf("%d",&num);
				count_bit(num);
			}
			break;
			case 2: {
				int num;
				int n = 0;
				printf("input a number:");
				scanf("%d",&num);
				num = (((num ^ (num+1))+1)>>1);
				while(num) {
					num>>=1;
					n++;
				}
				n-=1;
				printf("first 0  offset bit %d \n",n);
			}
			case 3:
				{
					// 2^n
					#define POWER2(n)  (1<<n)
					// plus:1   negative：0 
					#define sign(ch)  !(POWER2(7)&ch)
					char num = -2;
					char a=0;
					printf("input a number:");
					scanf("%d",&num); 
					if(sign(num))
					    a = num;
					else
						a = ~num+1; 
					printf("ddddd %d \n",a);				
				}
				break;
			default:
				break;
		}
		printf("input a cmd again?");
	}
	return 0;
}
typedef signed char S8;
typedef signed int  S32;
typedef unsigned char U8;
typedef unsigned int  U32;
int bitextend(void)
{// platform:DEV-C++ 
     signed   char  s8 = ~0;
     unsigned char  u8 = ~0;
     unsigned int   u32 = ~0;
     signed   int   s32 = ~0;
     /* 
      *  BYTE -> DWORD         ①unsigned char 高位都补0,值不变 
      *                        ②  signed char bit7为0，补0;为1，补1 
      *   %d %x %X都是输出整型 
      */
     printf("%d %u \n",u8,u8);//  255,255
     printf("%d %u \n",s8,s8);//  -1,8F
     printf("%d %u \n",(U8)0x6E,(U8)0x6E);//  0x64=110,110
     printf("%d %u \n",(S8)0xFE,(S8)0xFE);//  -2,8F-1

     printf("%d %u %d %u\n",s8,s8,u32,u32);//-1,8F,-1,8F 
}


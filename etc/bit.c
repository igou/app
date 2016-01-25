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
					// plus:1   negative£º0 
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

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
			default:
				break;
		}
		printf("input a cmd again?");
	}
	return 0;
}

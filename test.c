#include<stdio.h>
#include<string.h>

 
int main(void)
{
    int entry=0;
    
    scanf("%d",&entry);
    
	switch(entry)
	{
		case 1:
			printf("Demo 1:\n    	 result: %d\n",1<<1+1&7); //  (2<<(2+3))&7 算术>移位>位运算 
			break;
		case 2:{
				char q[]="heltoworld";
				char * p=q;
				int a=10;
				/*printf的运行顺序有关
				 * (*p)++  1，打印的是(*p)的值，++由于是右++，所以打印值不会是加1的值；2，(*p)++有写操作，注意p指向内容的可读属性； 
				 *  *p++,*(p++)是等同的，单目运算符结合方向由右向左 *(p++),所以是先p+1, 于是右++,所以*p的值是去加1以前的地址的值； 
				 */
		  		printf("Demo 2:   %c %c %c\n",*p++,*(p++),(*p)++); //从右往左计算 
		  		printf("%d,%d\n",a,a=a+1);
				printf("Demo 2:   %c\n",(*p)++);
				printf("%s",q); 
			}
			break; 
		case 3:{ 
			#if 1
			char *p ="helloworld";
			printf("Demo 3:    %c",(*p)++); // execute error 。(*p)++--------> write  
			#else
			char q[] ="helloworld";
			char *p = ;
			printf("Demo 3:    %c",(*p)++); // execute ok
			#endif
			} 
			break; 
		default:
			break;	
	} 

	return 0;
}

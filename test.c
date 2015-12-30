#include<stdio.h>
#include<string.h>
// int a=1; int b=a; build error  [constant value]
void error_sizeof_example(char str[])
{
	int i =sizeof(str)/sizeof(str[0]); 
	printf("%d %d\n",i,sizeof(str[0]));
} 
int f1(int para)
{
	printf("function 1\n");
	return 0;
}
int f2(int para)
{
	printf("function 2\n");
	return 0;
}
int f3(int para)
{
	printf("function 3\n");
	return 0;
}
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
		case 4:
		{
		//#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL    // build error 数字后面加UL,不是括号后面 
		#define SECONDS_PER_YEAR (60UL* 60 * 24 * 365)
		printf("%d\n",SECONDS_PER_YEAR);	
		} 
		break;
		case 5:
		{
		  char str[]="hello";
		/*sizeof用于数组，只能测出静态数组的大小，无法检测动态分配的或外部数组大小(在函数内使用 void example(char str[]))*/
		int i =sizeof(str)/sizeof(str[0]);
		printf("%d \n",i); //包括末尾的0; 
		error_sizeof_example(str);  /*函数内的str实际只是一个指向字符串的指针，没有任何额外的与数组相关的信息，
									  因此sizeof作用于其上只将其当指针看，一个指针为4个字节，因此返回4*/
		} 
		break;
		case 6:
			{
			 char a;
			 char *str=&a;
			 strcpy(str,"hello");//C语言标准库函数strcpy，把从src地址开始且含有'\0'结束符的字符串复制到以dest开始的地址空间 
			 printf(str); //虽然可以正确输出结果，但因为越界进行内在读写可能会导致程序崩溃 
			 }
			 break;
		case 7:
		  {//中括号不能少，不然声明在执行语句之后[Error] a label can only be part of a statement and a declaration is not a statement
		  int i;
		  int (*s[10])(int)={0}; //函数指针数组    int function(int para) 
		  s[0] = f1;
		  s[1] = f2;
		  s[2] = f3;
		  for(i=0;s[i]!=0;i++)
		  	s[i](1);// or (*s[i])(1);
	      } 
		  break;
		  case 8:
		  	{
		  		int a=69,b=96;
		  	  printf("%d %d\n",a,b);
			  a=a+b;b=a-b;a=a-b;
			  printf("chg:%d %d\n",a,b);
			  a=a^b;b=a^b;a=a^b;
			  printf("chg:%d %d\n",a,b);
			  a^=b^=a^b;// fixme:i dont know
			  printf("chg:%d %d\n",a,b);			  
			}
			break;
            case 9:
			{
				int a,b,c;
				c=9;
				c=c++%5;//c会修改两次，行为未定义 
				b=c;
				printf("%d\n",b);			
			 } 
            break;
		default:
			break;	
	} 

	return 0;
}

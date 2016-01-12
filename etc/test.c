#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
int f4(int para)
{
	printf("function 4:return ptr point to function\n");
	return 0;
}
/*f是函数，没有参数，返回指向一个函数的指针；这个被指向的函数有一个int型形参，且返回一个int值*/
int (*pfun_return(void))(int)
{
    return f4;//fun是个函数名，必须具备一个int形参、返回int值的要求
}
#if 0
void __restrict(const float* a,
                const float* b,
                float* c)
{
	/*不能优化，因为a[0]和c[0]有可能指向同一个地址，下面两句就不能优化*/
	c[0] = a[0] * b[0];
	c[1] = a[0] * b[0];
	c[2] = a[0] * b[0] * a[1];
	c[3] = a[0] * a[1];
	c[4] = a[0] * b[0];
	c[5] = b[0];
}
#else
void __restrict_1(const float* __restrict__ a,
                  const float* __restrict__ b,
                  float* __restrict__ c)
{
	/*编译器会如此优化，告诉了编译器这些指针都是有限制的*/
	float t0 = a[0];
	float t1 = b[0];
	float t2 = t0 * t2;
	float t3 = a[1];
	c[0] = t2;
	c[1] = t2;
	c[4] = t2;
	c[2] = t2 * t3;
	c[3] = t0 * t3;
	c[5] = t1;
}
void restrict___(char * __restrict__ str)
{
	int n;
	int ar[10];
	int * __restrict__ restar=(int *)malloc(10*sizeof(int));
	int *par=ar;
	for(n=0; n<10; n++) {
		par[n]+=5;
		restar[n]+=5;
		ar[n]*=2;
		par[n]+=3;
		restar[n]+=3; /*restar有限制，程序员告诉了编译只能通过该
						指针访问该对象，所以编译器就优化了restart[n]+=8；*/
	}
}
#endif
int main(void)
{
	int entry=0;

    printf("input cmd:");
	while(scanf("%d",&entry)!=EOF){

	switch(entry) {
		case 1:
			printf("Demo 1:\n    	 result: %d\n",1<<1+1&7); //  (2<<(2+3))&7 算术>移位>位运算
			break;
		case 2: {
			char q[]="heltoworld";
			char * p=q;
			int a=10;
			/*printf的运行顺序有关
			 * (*p)++  1，打印的是(*p)的值，++由于是右++，所以打印值不会是加1的值；2，(*p)++有写操作，注意p指向内容的可读属性；
			 *  *p++,*(p++)是等同的，单目运算符结合方向由右向左 *(p++),所以是先p+1, 由于是右++,所以*p的值是取加1以前的地址的值；
			 */
			printf("Demo 2:   %c %c %c\n",*p++,*(p++),(*p)++); //从右往左计算
			printf("%d,%d\n",a,a=a+1);
			printf("Demo 2:   %c\n",(*p)++);
			printf("%s",q);
		}
		break;
		case 3: {
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
		case 4: {
			//#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL    // build error 数字后面加UL,不是括号后面
#define SECONDS_PER_YEAR (60UL* 60 * 24 * 365)
			printf("%d\n",SECONDS_PER_YEAR);
#define  ADD(m)  do{\
	printf(#m"=%d\n",m);\
}while(0) //usage: #
			ADD(9);
		}
		break;
		case 5: {
			char str[]="hello";
			/*sizeof用于数组，只能测出静态数组的大小，无法检测动态分配的或外部数组大小(在函数内使用 void example(char str[]))*/
			int i =sizeof(str)/sizeof(str[0]);
			printf("%d \n",i); //包括末尾的0;
			error_sizeof_example(str);  /*函数内的str实际只是一个指向字符串的指针，没有任何额外的与数组相关的信息，
								  因此sizeof作用于其上只将其当指针看，一个指针为4个字节，因此返回4*/
		}
		break;
		case 6: {
			char a;
			char *str=&a;
			strcpy(str,"hello");//C语言标准库函数strcpy，把从src地址开始且含有'\0'结束符的字符串复制到以dest开始的地址空间
			printf(str); //虽然可以正确输出结果，但因为越界进行内在读写可能会导致程序崩溃
		}
		break;
		case 7: {
			//中括号不能少，不然声明在执行语句之后[Error] a label can only be part of a statement and a declaration is not a statement
			int i;
			typedef int(*fun)(int); //case 1
			fun f[10];
			int (*s[10])(int)= {0}; //case 2,函数指针数组    int function(int para)
			int (*pfun_return(void))(int); //声明。         FIXME:定义指针试验失败 
			f[0] = f1;
			f[1] = f2;
			f[2] = f3;			
			for(i=0; f[i]!=0; i++)
				f[i](1);// or (*s[i])(1);
		    pfun_return()(2);
		}
		break;
		case 8: {
			int a=69,b=96;
			printf("%d %d\n",a,b);
			a=a+b;
			b=a-b;
			a=a-b;
			printf("chg:%d %d\n",a,b);
			a=a^b;
			b=a^b;
			a=a^b;
			printf("chg:%d %d\n",a,b);
			a^=b^=a^b;// fixme:a is wrong
			printf("chg:%d %d\n",a,b);
		}
		break;
		case 9: {
			int a,b,c;
			c=9;
			c=c++%5;//c会修改两次，行为未定义
			b=c;
			printf("%d\n",b);
		}
		break;
		case 10:
#if 1
#define BUILD_BUG_ON(condition)  (sizeof(char[1-2*!!(condition)])) //这里的!!是为了处理传入宏参数为表达式的 
#else
			/* linux macros */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#endif
#define MAC1 1
#define MAC2 2
			BUILD_BUG_ON(MAC1 == MAC2);//检查宏定义的值是否一致
			break;
		case 11: {
#define TYPE_CHK(type,VA)  ({type std; \
	(&std==&VA);\
	1;})
			char b;
			TYPE_CHK(int ,b);
		}
		break;
		case 12:
		    {
		        char str[]="hello";
		        void * nul=(void *)str;
		        //*nul='a'; // build error:complier don't know the length of *nul due to the type void *
            }
            break;
		default:
			break;
	}
	 printf("input cmd again or exit:");
}
	return 0;
}

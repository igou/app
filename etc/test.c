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
/*f�Ǻ�����û�в���������ָ��һ��������ָ�룻�����ָ��ĺ�����һ��int���βΣ��ҷ���һ��intֵ*/
int (*pfun_return(void))(int)
{
    return f4;//fun�Ǹ�������������߱�һ��int�βΡ�����intֵ��Ҫ��
}
#if 0
void __restrict(const float* a,
                const float* b,
                float* c)
{
	/*�����Ż�����Ϊa[0]��c[0]�п���ָ��ͬһ����ַ����������Ͳ����Ż�*/
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
	/*������������Ż��������˱�������Щָ�붼�������Ƶ�*/
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
		restar[n]+=3; /*restar�����ƣ�����Ա�����˱���ֻ��ͨ����
						ָ����ʸö������Ա��������Ż���restart[n]+=8��*/
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
			printf("Demo 1:\n    	 result: %d\n",1<<1+1&7); //  (2<<(2+3))&7 ����>��λ>λ����
			break;
		case 2: {
			char q[]="heltoworld";
			char * p=q;
			int a=10;
			/*printf������˳���й�
			 * (*p)++  1����ӡ����(*p)��ֵ��++��������++�����Դ�ӡֵ�����Ǽ�1��ֵ��2��(*p)++��д������ע��pָ�����ݵĿɶ����ԣ�
			 *  *p++,*(p++)�ǵ�ͬ�ģ���Ŀ�������Ϸ����������� *(p++),��������p+1, ��������++,����*p��ֵ��ȡ��1��ǰ�ĵ�ַ��ֵ��
			 */
			printf("Demo 2:   %c %c %c\n",*p++,*(p++),(*p)++); //�����������
			printf("%d,%d\n",a,a=a+1);
			printf("Demo 2:   %c\n",(*p)++);
			printf("%s",q);
		}
		break;
		case 3: {
#if 1
			char *p ="helloworld";
			printf("Demo 3:    %c",(*p)++); // execute error ��(*p)++--------> write
#else
			char q[] ="helloworld";
			char *p = ;
			printf("Demo 3:    %c",(*p)++); // execute ok
#endif
		}
		break;
		case 4: {
			//#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL    // build error ���ֺ����UL,�������ź���
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
			/*sizeof�������飬ֻ�ܲ����̬����Ĵ�С���޷���⶯̬����Ļ��ⲿ�����С(�ں�����ʹ�� void example(char str[]))*/
			int i =sizeof(str)/sizeof(str[0]);
			printf("%d \n",i); //����ĩβ��0;
			error_sizeof_example(str);  /*�����ڵ�strʵ��ֻ��һ��ָ���ַ�����ָ�룬û���κζ������������ص���Ϣ��
								  ���sizeof����������ֻ���䵱ָ�뿴��һ��ָ��Ϊ4���ֽڣ���˷���4*/
		}
		break;
		case 6: {
			char a;
			char *str=&a;
			strcpy(str,"hello");//C���Ա�׼�⺯��strcpy���Ѵ�src��ַ��ʼ�Һ���'\0'���������ַ������Ƶ���dest��ʼ�ĵ�ַ�ռ�
			printf(str); //��Ȼ������ȷ������������ΪԽ��������ڶ�д���ܻᵼ�³������
		}
		break;
		case 7: {
			//�����Ų����٣���Ȼ������ִ�����֮��[Error] a label can only be part of a statement and a declaration is not a statement
			int i;
			typedef int(*fun)(int); //case 1
			fun f[10];
			int (*s[10])(int)= {0}; //case 2,����ָ������    int function(int para)
			int (*pfun_return(void))(int); //������         FIXME:����ָ������ʧ�� 
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
			c=c++%5;//c���޸����Σ���Ϊδ����
			b=c;
			printf("%d\n",b);
		}
		break;
		case 10:
#if 1
#define BUILD_BUG_ON(condition)  (sizeof(char[1-2*!!(condition)])) //�����!!��Ϊ�˴���������Ϊ���ʽ�� 
#else
			/* linux macros */
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#endif
#define MAC1 1
#define MAC2 2
			BUILD_BUG_ON(MAC1 == MAC2);//���궨���ֵ�Ƿ�һ��
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

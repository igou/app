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
			printf("Demo 1:\n    	 result: %d\n",1<<1+1&7); //  (2<<(2+3))&7 ����>��λ>λ���� 
			break;
		case 2:{
				char q[]="heltoworld";
				char * p=q;
				int a=10;
				/*printf������˳���й�
				 * (*p)++  1����ӡ����(*p)��ֵ��++��������++�����Դ�ӡֵ�����Ǽ�1��ֵ��2��(*p)++��д������ע��pָ�����ݵĿɶ����ԣ� 
				 *  *p++,*(p++)�ǵ�ͬ�ģ���Ŀ�������Ϸ����������� *(p++),��������p+1, ������++,����*p��ֵ��ȥ��1��ǰ�ĵ�ַ��ֵ�� 
				 */
		  		printf("Demo 2:   %c %c %c\n",*p++,*(p++),(*p)++); //����������� 
		  		printf("%d,%d\n",a,a=a+1);
				printf("Demo 2:   %c\n",(*p)++);
				printf("%s",q); 
			}
			break; 
		case 3:{ 
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
		case 4:
		{
		//#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)UL    // build error ���ֺ����UL,�������ź��� 
		#define SECONDS_PER_YEAR (60UL* 60 * 24 * 365)
		printf("%d\n",SECONDS_PER_YEAR);	
		} 
		break;
		case 5:
		{
		  char str[]="hello";
		/*sizeof�������飬ֻ�ܲ����̬����Ĵ�С���޷���⶯̬����Ļ��ⲿ�����С(�ں�����ʹ�� void example(char str[]))*/
		int i =sizeof(str)/sizeof(str[0]);
		printf("%d \n",i); //����ĩβ��0; 
		error_sizeof_example(str);  /*�����ڵ�strʵ��ֻ��һ��ָ���ַ�����ָ�룬û���κζ������������ص���Ϣ��
									  ���sizeof����������ֻ���䵱ָ�뿴��һ��ָ��Ϊ4���ֽڣ���˷���4*/
		} 
		break;
		case 6:
			{
			 char a;
			 char *str=&a;
			 strcpy(str,"hello");//C���Ա�׼�⺯��strcpy���Ѵ�src��ַ��ʼ�Һ���'\0'���������ַ������Ƶ���dest��ʼ�ĵ�ַ�ռ� 
			 printf(str); //��Ȼ������ȷ������������ΪԽ��������ڶ�д���ܻᵼ�³������ 
			 }
			 break;
		case 7:
		  {//�����Ų����٣���Ȼ������ִ�����֮��[Error] a label can only be part of a statement and a declaration is not a statement
		  int i;
		  int (*s[10])(int)={0}; //����ָ������    int function(int para) 
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
				c=c++%5;//c���޸����Σ���Ϊδ���� 
				b=c;
				printf("%d\n",b);			
			 } 
            break;
		default:
			break;	
	} 

	return 0;
}

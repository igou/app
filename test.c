#include<stdio.h>
#include<string.h>

 
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
		default:
			break;	
	} 

	return 0;
}

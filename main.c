#include <stdio.h>
#include <stdlib.h>

#include <minwindef.h>
#include <winnt.h>
#include <minwinbase.h> 
//#include <winbase.h>
#include <fileapi.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct {
int a1;
}str1_t;
typedef struct{
int b1;
}str2_t;
typedef union {
str1_t a;
str1_t b;
int  c;
char d;
}com_t;
com_t  test;
const char * p; 
const int a_a;

int _strcmp(const char *s1,const char *s2)
{
	int l1,l2,index=0;
	if(s1==NULL || s2==NULL)
		return -2;
	l1 = strlen(s1);
	l2 = strlen(s2);
	printf("xxxxxxxxxxxxx%d %d \n",l1,l2);
	while(s1[index] != 0 && s2[index] != 0)
	{
		if(s1[index]<s2[index])
			return -1;
		else if(s1[index]>s2[index])
			return 1;
		else
			index++;	
	}
	if(l1 == l2)
		return 0;
	else
		return ((l1<l2)?-1:1);
}
int _str_revise(char * s) 
{
	int len,i,j;		char tmp;
	if(s == NULL)
	 return -1;
	len = strlen(s);
	for(i=0;i<len;i++)
		printf("%c ",s[i]);
	printf("%d \n",len); 
	for(i=0;i<(len/2);i++){

		tmp = s[i];
		printf("\n %d \n",len-i-1); 
	     s[i]= s[len-1-i];
		 s[len-1-i] = tmp;
	}
	for(i=0;i<len;i++)
		printf("%c ",s[i]);
	printf("\n"); 
   return 0;
}
void test_func(com_t *input)
{
//	str1_t *var1 =(str2_t *)&input->b;
//	var1->a1 =2;
	//printf("test:%d",var1->a1); 

}
int main(int argc, char *argv[]) {
	#if 0
str1_t v1;
str2_t v2; 
char s;
v2.b1 = 5;
 v1.a1 =100;
 test_func((com_t *)&v2);
 p = &s;
 #else
 //int i = _strcmp("heooo","hello");
 //1printf("ttttttttttt %d dddddddddd\n",i);
 _str_revise("abcdef");
 #endif
}

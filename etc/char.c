#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _strcmp(const char *s1,const char *s2)
{
	int l1,l2,index=0;
    
	if(s1==NULL || s2==NULL)
		return -2;
	l1 = strlen(s1);
	l2 = strlen(s2);
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
void swap(char *a,char *b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}
int _str_reverse(char * s) 
{
	int len,i,j;		char tmp;
	if(s == NULL)
	 return -1;
	len = strlen(s);
	for(i=0;i<len;i++)
		printf("%c ",s[i]);
	printf("\n");
	for(i=0;i<(len/2);i++){
		swap(s+i,s+len-1-i);
		#if 0
		 tmp = s[i];
	     s[i]= s[len-1-i];
		 s[len-1-i] = tmp;
		#endif 
	}
	for(i=0;i<len;i++)
		printf("%c ",s[i]);
	printf("\n"); 
   return 0;
}
/*统计字母出现频率 
 */
int alphabet_fre(const char *str)
{
#define LEN 26
	int i=0;
	char cmp[LEN]={0},ch;
	
	if(str == NULL)
		return -1;
	ch = str[i];
	while(ch){
		cmp[ch-'a']++;
		i++;
		ch = str[i]; 
	}
	for(i=0;i<LEN;i++)
	{
		if(cmp[i]>0)
			printf("%c:%d ",'a'+i,cmp[i]);
	}
	printf("\n");
#undef LEN
}
//TODO:多个字符长度相等且为最大的情况 
int alphabet_longest(const char *str)
{
	char lgtch;
	int i=1,l=0;
	int  lgt=0,count=0;
	if(str == NULL)
		return -1;

	if(str[0] == 0)
          return 0;
   // here: 至少有一个字符 
	lgtch = str[0];
	lgt = 1;
	while(str[i++]){//比较前后字符，注意通过手段判断两个位置都是有效字符 ; 
		if(!(str[i-1]^str[i])){
	         count++;		
	         }
        else{
            if(count>=lgt)
              {
                 lgt =count;
                 lgtch = str[i-1];
              }
            count = 1;       
        }
  }
  	printf("%c:%d \n",lgtch,lgt);
} 
//两个for循环，打印*或space通过条件语句判断(通过*的index范围来判断) 
int  print_star(void)
{
    int i,j;
    #define T 3
    #if 1
    #define N 3 
    #else
    #define N (2*T-1)
    #endif
    for(i=0;i<N/2+1;i++){
        for(j=0;j<N;j++){
            if(j>=((N>>1)-i)&& j<=((N>>1)+i))  // N/2就是最中间位置的index 
                printf("*");
            else
                printf(" ");
        }
    printf("\n");
    }    
    for(i=0;i<N/2;i++){
        for(j=0;j<N;j++){
            if(j>i&& j<N-1-i)  //  
                printf("*");
            else
                printf(" ");
        }
    printf("\n");
    }    
}

int main(int argc, char *argv[]) {
 char str[]="khdffds";

 alphabet_fre("helllloworlkd");
 alphabet_longest("helloowoooorldddddddddddd");
 _str_reverse(str);
  /*Fix: the str should be modifiable==>
                      _str_reverse("abcdef");Error:it will occur 
		      seg fault if modify data of "acdef"
		    */
 print_star();
}

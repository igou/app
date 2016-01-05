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
int _str_reverse(char * s) 
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
int main(int argc, char *argv[]) {
 char str[]="abcdef";
 _str_reverse(str); /*Fix: the str should be modifiable==>
                      _str_reverse("abcdef");Error:it will occur 
		      seg fault if modify data of "acdef"
		    */
 #endif
}

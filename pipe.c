#include<stdio.h>
#include<unistd.h>

int p_fd[2];
int ret;
pid_t pid;
char input;
char str[20]={"hello,world\n"},buf[20]={0};
int main(void)
{
	ret = pipe(p_fd);
	if (ret < 0)
	{
	perror("pipe create error\n");
	}
	if((pid = fork())==0)
	{
	printf("this is child\n");
	close(p_fd[0]);
	while(1)
	{
	scanf("%c",&input);
	getchar();
	if(input == 'a')
	{
	str[0] +=1;
	input = 0;
	write(p_fd[1],str,strlen(str));
	}
	else if(input == 'q')
	{
	close(p_fd[1]);
	}
//	waitpid(pid,NULL,0);
	}
	}
	else
	{int r;
	printf("father\n");
	close(p_fd[1]);
	while(1)
	{
	if((r = read(p_fd[0],buf,32))>0) 
		printf("recv:%s,,%d\n",buf,r);
	else        
{		close(p_fd[0]);}
	}
	}
return 1;
}

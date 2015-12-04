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
	while(1)
	{
	printf("input:\n");
	scanf("%c",&input);
	getchar();
	if(input == 'a')
	{
	//close(p_fd[0]);
	//write(p_fd[1],str,strlen(str));
	printf("xxxxxxxxxxxxxxxxxxxxxxxx :%c\n",input);
	}
	else if(input == 'q')
	{
	break;
	}
	//waitpid(pid,NULL,0);
	}
	}
	else
	{
	printf("father\n");
	while(1)
	{
	//close(p_fd[1]);
	//read(p_fd[0],buf,strlen(str));
	sleep(1);
	printf("recv:out\n");
	}
	}
return 1;
}

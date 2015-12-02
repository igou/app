#include<stdio.h>
#include<pthread.h>
typedef void *(*call)(void *);
pthread_mutex_t mutex;
int add = 0;
void * fun_1(void *no)
{int i=0;
	
	for(i=0;i<10;i++){
//	pthread_mutex_lock(&mutex);
	add++;
	sleep(2);
	printf("1:%d\n",add);
//	pthread_mutex_unlock(&mutex);
}
}
void * fun_2(void *no)
{
int i = 0;
	for(i=0;i<20;i++){
//	pthread_mutex_lock(&mutex);
	add = add + 2;
	sleep(2);
	printf("2:%d\n",add);
//	pthread_mutex_unlock(&mutex);
	}
}



int main(void)
{
int ret;
pthread_t p1,p2;
void *res;
ret = pthread_create(&p1,NULL,fun_1,NULL);
if(ret < 0)
{
	perror("pthread error\n");
}

ret = pthread_create(&p2,NULL,fun_2,NULL);
if(ret < 0)
{
	perror("pthread error  222\n");
}
pthread_join(p1,&res);

pthread_join(p2,&res);
return  0;
}

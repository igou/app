#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void insert_sort(int a[],int length)
{
	int index;
	int tmp;
	int i;
	
	for(i=0;i<length;i++)
		printf("%d,",a[i]);	
		printf("\n\n");
	for(index=1;index<length;index++)
	{
		if(a[index]<a[index-1])//if not ,will sort again
		{
			i = index;
			while(i>0&&a[i]<a[i-1])
				{
					tmp = a[i];
					a[i]= a[i-1];
					a[i-1]= tmp;
					i--;					
				}
			}
	}
	for(i=0;i<length;i++) 
		printf("%d,",a[i]);	
}

/*�ѳ�����ʵ�����ȶ��У���һ����ȫ������
 * �Է�Ҷ�ӽڵ�(n/2)���жѵ���,ÿ����һ���ڵ㣬�����ܵ��������������ʣ���Ҫ���������� �� 
 */
 #define Xheaptype int 
typedef Xheaptype hp_t; //heap type
#define LEFT(x)  (x*2+1)
#define RIGHT(x) (x*2+2)
/*�ٶ��ڵ�n������������Ϊheap����ǰ����n���������ӽڵ�Ĺ�ϵ
 * �ú������ɽڵ�n,���µ���
 */
void heapify(hp_t h[],int size,int n) 
{
	int l = LEFT(n),r = RIGHT(n);
	int max = n;// index of maximum member
	
	// �ж�index���Ƚ�ֵ 
	if(l<size)  
		max =  (h[l]>h[max]) ? l : max;
	if(r<size)
		max =  (h[r]>h[max]) ? r : max; 
	
	if(max != n)  //�ж�max�Ƿ�ı䣬û�б仯����ʾ���������������� 
	{
		 // ����ֵ 
	   hp_t tmp;
	   tmp    = h[max];
	   h[max] = h[n];
	   h[n]   = tmp;
	     // ���������ĸ��ڵ�ֵ���ˣ����ܲ��������� ������Ҫ����������
		 heapify(h,size,max);
	}
}
// ������Ҷ��� 
int create_heap(hp_t a[],int size)
{
	int i ;
	for( i = size/2; i>=0 ;i--)//��size��ż�޹� ��Ҷ�ӵ������ڵ��ڷ�Ҷ�ӵ�������i��ֵ������Χ�ˣ�heapify���ж� 
		heapify(a,size,i);  //�ֱ�Է�Ҷ�ӽڵ��index�ɴ�С���е��� 
		
	return 1;
}
	#define SIZE 5
	//hp_t a[SIZE];
	hp_t *a;
int heap(void)
{
	int i;
	a = (hp_t *)malloc(sizeof(hp_t)*(SIZE+2)); 
	printf("input %d int number\n",SIZE);
	
	for( i = 0;i<SIZE;i++)
		scanf("%d",&a[i]); 
	for(i = 0;i < SIZE;i++) 
		printf("%d ",a[i]);
	printf("\n");
	
	create_heap(a,SIZE);
	
	for(i = 0;i < SIZE;i++) 
		printf("%d ",a[i]);
		
	return 1;
}
int heap_sort(hp_t a[],int size)
{
	int l,i;
	hp_t tmp;
	// �����ѣ�Ȼ�����ֵ������뽻�����ٽ��ѳ��ȼ�һ��ѭ�����ѳ���Ϊ0�� 
	for(l = size;l>0;l--){
	for(i = l/2;i>=0;i--)
		heapify(a,l,i);
	tmp 	= a[0];
	a[0] 	= a[l-1];
	a[l-1] = tmp;
	}
	printf("\n");
	for(i=0;i<size;i++)
		printf("%d ",a[i]); 
		
	return 1; 
} 
int insert_heap(hp_t a[],int size,hp_t mem)
{
		int i ;
	a[size-1]=mem;
	for( i = size/2; i>=0 ;i--)
	heapify(a,size,i); 
		printf("\n");
	for(i=0;i<SIZE+2;i++)
		printf("%d ",a[i]); 
	return 1;
}
int delete_heap(hp_t a[],int size,hp_t mem)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(mem == a[i])
		  {a[i] = a[size-1];break;}
	}
	if(i>=size)
		return -1;//not found
	if(i==size-1)
		return size-1;//heap size
	for(i=size-1;i>=0;i--)
		heapify(a,size-1,i); 
	printf("\n");
	for(i=0;i<size-1;i++)
		printf("%d ",a[i]); 
		return size-1;
}


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int bubble_sort(int a[],int size)
{
	int i,j;
	
	printf("input %d number:",size);
	for(i=0;i<size;i++)
		scanf("%d",&a[i]);
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
	printf("\n");
/***********************************************************************************************/
	for(i=0;i<size;i++)
		for(j=1;j<size-i;j++) //����С���ŵ����ϣ��´ξͲ���Ҫѭ�� 
		{ 
		 if(a[j]>a[j-1]){ // ��������Ԫ�رȽϽ��� 
		 		int tmp = a[j];
		 		a[j]=a[j-1];
		 		a[j-1] =tmp;
			} 
		}
/***********************************************************************************************/ 
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
	printf("\n");
}
int quick_sort(int a[],int size) 
{
	int slot,i,j,mid,tmp;
/***********************************************************************************************/
	if(size <= 1)  //�������� 
		return 1;
	slot = a[0];
	i=0;j=size-1;
	while(i<j) 
	{/* 1, slotֵѡ����Ͳ���ı� 
	  * 2��i->   <-j 
	  */ 
		while(i<j)
		{
			if(a[j]<slot){			
			   tmp =a[j];a[j]=a[i];a[i]=tmp;
			  break;
			}
			j--;
		}
		while(i<j)
		{
			if(a[i]>slot){
			   tmp =a[i];a[i]=a[j];a[j]=tmp;
			break;
			}
			i++;
		}		
	}
	mid = i+1; //i��jΪ�ָ�� 
	quick_sort(&a[0],mid);
	quick_sort(&a[mid],size-mid);
 return 1;
/***********************************************************************************************/	
}
int quick_handler(int a[],int size )
{
	int i,j;
		printf("input %d number:",size);
	for(i=0;i<size;i++)
		scanf("%d",&a[i]);
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
	printf("\n");
	
	quick_sort(a,size);
	
	for(i=0;i<size;i++)
		printf("%d ",a[i]);
	printf("\n");
}
#if 1
int main(int argc, char *argv[]) {
	#define  ADD(m)  printf(#m"=%d\n",m)
	int a[6]={0};
	ADD(9); 
	do
	{
		quick_handler(a,sizeof(a)/sizeof(a[0]));
	}while(getchar() != 'q');
	return 0;
}
#else
int main(int argc, char** argv) {
	heap();
	heap_sort(a,SIZE);
	insert_heap(a,SIZE+1,20);
	heap_sort(a,SIZE+1);
	delete_heap(a,SIZE+1,6);
	heap_sort(a,SIZE);
	return 0;
}
#endif


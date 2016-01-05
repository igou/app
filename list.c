#include<stdio.h> 
#include<stdlib.h>

typedef struct __node{
struct {
int value;
struct __node * next;
};
}node;

static node *sl_head;
void main_start(void)
{
	printf("macro test\n");
}
void init_node(node **p)
{
	(*p)=(node *)malloc(sizeof(node));
	(*p)->next = NULL; //Notice ѭ�������� 
	(*p)->value = ~0L;
}
node * node_new(void)
{
	return (node *)malloc(sizeof(node));
}
node * node_alloc(int v)
{
	node *p=NULL;
	p = node_new();
	if(p != NULL)
		p->value = v;
	return p;
}
void node_free(node *n)
{
	if(n != NULL)
		free(n);
} 
void __node_add(node *prev,node *next)
{
	next->next = prev->next; //��prevΪ���������һ�������ﲻ�����next���Ƿ�Ϊnull���������Լ���֤�� 
	prev->next = next;
}
void __node_del(node *prev,node *node)
{
	prev->next = node->next; //��nextΪ���������һ�������ﲻ�����next���Ƿ�Ϊnull���������Լ���֤�� 
}
/*	stack */
void  node_add(node *head,node * new) 
{
	__node_add(head,new);
}
/*  queue*/
void  node_add_tail(node *head,node * new) 
{
			
}
void node_insert(node *head,node *new)
{
	__node_add(head,new);	
}
int node_del(node *prev,node *node)
{
	__node_del(prev,node); 
}

/*   platform */
int add_node(int v,node *new)
{
	node * p;
	if (new == NULL)
	  return 1;
	
	for(p = sl_head;p;p=p->next){
			if(v == p->value){
				node_add(p,new);
				return 0;
			 }
	}	
	 return 1;//error
}
int del_node(int v)
{
// todo ��ʹ�ö���ָ����Բ���ά��prevָ�� 
  node *p,*prev=NULL;
  /*case: head is matching*/
  for(p = sl_head;p;prev = p,p=p->next){
  	   if(v == p->value && p != sl_head){
  	   	 node_del(prev,p);
  	   	 return 0;
		 }
  }
   return 1;//error
}
// ����ָ��ʾ�� 
int del_nodes(int v)
{
	node **p=&sl_head;
	for(;(*p)->next;p=&(*p)->next){
		if(v == (*p)->next->value){
			node_del(*p,(*p)->next);//���ڵ�������Ļ���ɾ�����һ��ʱ��(*p)->next�ᱻ��ֵΪNULL,ִ����һ�� p=&(*p)->next�����(ȡNULL�ĵ�ַ) ����Ȼѭ��������Ļ���OK 
			return 0;// it can fix the issue above:skip p=&(*p)->next
		}
	}
	return 1;
}
int main(void) 
{
	int i;
	node * pos,*new,*tmp;
	init_node(&sl_head);//���봫�����ָ�룬���ܸ�ȫ�ֱ���sl_head��ֵ
	for(i=0;i<6;i++){
		new = (node *)node_alloc(5-i);
		node_add(sl_head,new);
	}
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->value);
	del_nodes(4);
	add_node(0,node_alloc(1003));	
	del_nodes(1);
	del_nodes(5);
	printf("------------------------\n");
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->value);
	printf("step1\n");	
		for(pos=sl_head->next;pos;pos=tmp){
			  node_del(sl_head,pos);
			  tmp = pos->next;//notice :before free,recored next field
			   node_free(pos); 
	}
		
	printf("ok\n");
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->value);
	printf("step2\n");
	node_free(sl_head); //fix:sl_head NOT free
} 

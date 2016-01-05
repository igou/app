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
	(*p)->next = NULL; //Notice 循环单链表 
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
	next->next = prev->next; //若prev为单链表最后一个，这里不检查其next域是否为null，调用者自己保证。 
	prev->next = next;
}
void __node_del(node *prev,node *node)
{
	prev->next = node->next; //若next为单链表最后一个，这里不检查其next域是否为null，调用者自己保证。 
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
// todo ：使用二级指针可以不用维护prev指针 
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
// 二级指针示例 
int del_nodes(int v)
{
	node **p=&sl_head;
	for(;(*p)->next;p=&(*p)->next){
		if(v == (*p)->next->value){
			node_del(*p,(*p)->next);//对于单向链表的话，删除最后一个时，(*p)->next会被赋值为NULL,执行下一句 p=&(*p)->next会出错(取NULL的地址) ；当然循环单链表的话就OK 
			return 0;// it can fix the issue above:skip p=&(*p)->next
		}
	}
	return 1;
}
int main(void) 
{
	int i;
	node * pos,*new,*tmp;
	init_node(&sl_head);//必须传入二级指针，才能给全局变量sl_head赋值
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

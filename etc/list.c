#include<stdio.h> 
#include<stdlib.h>


typedef struct node{
    struct node *next;
    struct node *prev;    
    union {
        int  num;
        char alpha; 
        void * p;
    }data;
}node_t;
int list_init(node_t *node)
{
    node->next = node;
    node->prev = node;
}
int list_add(node_t *head,node_t *node)
{
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;    
}
int list_add_tail(node_t *head,node_t *node)
{
    node->next = head;
    node->prev = head->prev;
    head->prev->next = node;
    head->prev = node;    
}
int print_list(node_t *head)
{
    node_t *node;
   /* 此处遍历链表时，head头只是作为一个入口点，其中不包括有意义的数据 ,
     *否则在遍历的条件处理上就没有这么简单
     */ 
    for(node = head->next;node != head;node=node->next){
         printf("%c ",node->data.alpha);        
    }
    printf("\n");
}
int list_reverse(node_t *head) 
{
    node_t *cur,*prev,*next; // miss *
    for(prev = head,next = NULL,cur = head->next;cur!= head;)//error:prev = NULL
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;     
    }
    cur->next = prev;//循环链表的反转，要多出个head特殊处理
}
int build_list(node_t *head)
{  
   char ch=0;
   node_t *node=NULL;
   
   printf("input\n");
   
   while((ch=getchar())!=EOF){
       getchar();
       node=(node_t *)malloc(sizeof(node_t));
       if(node != NULL){
               node->data.alpha = ch;
                list_add_tail(head,node); // head not init 
       }        
   } 
   print_list(head);
   list_reverse(head);
   print_list(head);
}
/*-------------------------------单链表实现----------------------------------------------*/ 

static node_t *sl_head;
void main_start(void)
{
	printf("macro test\n");
}
void single_init_node(node_t **p)
{
	(*p)=(node_t *)malloc(sizeof(node_t));
	(*p)->next = NULL; //Notice 循环单链表 
	(*p)->data.num = ~0L;
}
node_t * node_new(void)
{
	return (node_t *)malloc(sizeof(node_t));
}
node_t * node_alloc(int v)
{
	node_t *p=NULL;
	p = node_new();
	if(p != NULL)
		p->data.num = v;
	return p;
}
void node_free(node_t *n)
{
	if(n != NULL)
		free(n);
} 
//single linked list
void __single_node_add(node_t *prev,node_t *next)
{
	next->next = prev->next; //若prev为单链表最后一个，这里不检查其next域是否为null，调用者自己保证。 
	prev->next = next;
}
void __single_node_del(node_t *prev,node_t *node)
{
	prev->next = node->next; //若next为单链表最后一个，这里不检查其next域是否为null，调用者自己保证。 
}
/*	stack */
void  single_node_add(node_t *head,node_t * new) 
{
	__single_node_add(head,new);
}
/*  queue*/
void  single_node_add_tail(node_t *head,node_t * new) 
{
			
}
void single_node_insert(node_t *head,node_t *new)
{
	__single_node_add(head,new);	
}
int single_node_del(node_t *prev,node_t *node)
{
	__single_node_del(prev,node); 
}

/*   platform */
int single_add_node(int v,node_t *new)
{
	node_t * p;
	if (new == NULL)
	  return 1;
	
	for(p = sl_head;p;p=p->next){
			if(v == p->data.num){
				single_node_add(p,new);
				return 0;
			 }
	}	
	 return 1;//error
}
int del_node(int v)
{
// todo ：使用二级指针可以不用维护prev指针 
  node_t *p,*prev=NULL;
  /*case: head is matching*/
  for(p = sl_head;p;prev = p,p=p->next){
  	   if(v == p->data.num && p != sl_head){
  	   	 single_node_del(prev,p);
  	   	 return 0;
		 }
  }
   return 1;//error
}
// 二级指针应用于单链表示例 
int del_nodes(int v)
{
	node_t **p=&sl_head;
	for(;(*p)->next;p=&(*p)->next){
		if(v == (*p)->next->data.num){
			single_node_del(*p,(*p)->next);//对于单向链表的话，删除最后一个时，(*p)->next会被赋值为NULL,执行下一句 p=&(*p)->next会出错(取NULL的地址) ；当然循环单链表的话就OK 
			return 0;// it can fix the issue above:skip p=&(*p)->next
		}
	}
	return 1;
}
int main(void) 
{
	int i;
	node_t * pos,*new,*tmp;
	single_init_node(&sl_head);//必须传入二级指针，才能给全局变量sl_head赋值
	for(i=0;i<6;i++){
		new = (node_t *)node_alloc(5-i);
		single_node_add(sl_head,new);
	}
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->data.num);
	del_nodes(4);
	single_add_node(0,node_alloc(1003));	
	del_nodes(1);
	del_nodes(5);
	printf("------------------------\n");
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->data.num);
	printf("step1\n");	
		for(pos=sl_head->next;pos;pos=tmp){
			  single_node_del(sl_head,pos);
			  tmp = pos->next;//notice :before free,recored next field
			   node_free(pos); 
	}
		
	printf("ok\n");
	for(pos=sl_head->next;pos;pos=pos->next)
		printf("value:%d\n",pos->data.num);
	printf("step2\n");
	node_free(sl_head); //fix:sl_head NOT free
	
	/* { 
         node_t head={0};
        list_init(&head);
        build_list(&head);}
    */ 
} 

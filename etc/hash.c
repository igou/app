#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

struct h_node;
typedef struct h_node hnode_t;

#define HASH_MAX_SIZE 10
typedef struct hash {
	hnode_t *next;
} hash_head_t;

typedef struct h_node {
	union {
		int value;
		char * str;
	} data;
	hnode_t *next;
} hnode_t;

hash_head_t *head;
void hash_tbl_init(void)
{
	head = (hash_head_t *)malloc(sizeof(hash_head_t )*HASH_MAX_SIZE);
	memset(head,0x00,sizeof(hash_head_t )*HASH_MAX_SIZE);
}
void hash_add(hash_head_t *head,hnode_t * node)
{
	node->next = head->next;
	head->next = node;
}
int hash_insert(char * str)
{
	int key = 0,i=0,l=0,max = 5;
	hnode_t *node = NULL;
	char * new;

	l = strlen(str);
	if(l<5)//计算最多5个字符
		max = l;
	while(i++ < max) {
		key += str[i];
	}
	key %= HASH_MAX_SIZE;

	node = (hnode_t *)malloc(sizeof(hnode_t));
	if(node == NULL)
		return -1;

	new = (char *)malloc(l+1);

	if(new == NULL) {
		free(node);
		return -1;
	}
	strncpy(new,str,l+1);

	node->data.str = new;

	hash_add(&head[key],node);

	return 0;
}
// 1->exist -1->non-exist
int hash_find(char * str,hash_head_t *head)
{
	hnode_t * pos=NULL;
	for(pos = head->next; pos!=NULL; pos= pos->next) {
		if(strcmp(pos->data.str,str) == 0) {
			return 1;
		}
	}
	return -1;
}
int hash_search(char *str)
{
	int key = 0,i=0,l=0,max = 5;

	l = strlen(str);
	if(l<5)//计算最多5个字符
		max = l;
	while(i++ < max) {
		key += str[i];
	}
	key %= HASH_MAX_SIZE;

	return hash_find(str,&head[key]);
}
void hash_create(void)
{
	char ch,i=0;
	char buf[20] = {0};

	printf("input string:\n");

	while((ch = getchar()) != EOF) {
		buf[i++] = ch;
		if(ch == ' ' || ch == '\n') {
			buf[i-1] = 0;
			i=0;
			printf("one %d\n",strlen(buf));
			hash_insert(buf);
		}
	}
}
int main()
{
	char str[10] = {0};

	/*对于scanf以%s格式输入时候，“空格、换行符、TAB”等是作为两个数据的分隔符存在的，即分隔符前后是两个数据，读入时候分隔符不读入*/
	//sscanf("%s",str);
	//printf("%s\n",str);
	hash_tbl_init(); // error :miss init fun
	hash_create();

	printf("searcing\n");
	while(1) {
		scanf("%s",str);
		if(!strcmp(str,"over"))
			break;
		str[strlen(str)] = 0;
		if(1==hash_search(str)) // -1,1
			printf("Found\n");
		else
			printf("Not exist\n");
	}
	return 0;
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct tree{
struct tree * left;
struct tree * right;
int         value;
int count;
}tree_t;
int build_tree(tree_t ** proot,int value){
	tree_t *root=*proot; // point
	tree_t *left,*right;
	
	
	if(!root)
	  {
	  	root = (tree_t *)malloc(sizeof(tree_t));
	  	memset(root,0x00,sizeof(tree_t));
	  	root->value = value;
	  	root->count ++;
	   }
	else
	{
		if(value<root->value){
			if(root->left == NULL){
			left= (tree_t *)malloc(sizeof(tree_t));
			memset(left,0x00,sizeof(tree_t));
			root->left = left;
			left->value = value;
			left->count ++;
			}
			else{
			build_tree(&root->left,value);}
		}
		else if(value>root->value){
			if(root->right == NULL){
			right = (tree_t *)malloc(sizeof(tree_t));
			memset(right,0x00,sizeof(tree_t));
			root->right = right;
			right->value = value;
			right->count ++;
			}
			else{
			build_tree(&root->right,value);}
		}
		else
			root->count++;		
}
*proot=root;
return 0;
}
void visit(tree_t * root)
{
	printf("%c:%d  ",root->value,root->count);
}
int midorder(tree_t *root)
{
	if(root == NULL)
		return 1;

	midorder(root->left);
	visit(root);
	midorder(root->right);
	return 0;
}
int postorder(tree_t *root)
{
	if(root == NULL)
		return 1;

	postorder(root->left);
	postorder(root->right);
	visit(root);
	return 0;
}

int preorder(tree_t *root)
{
	if(root == NULL)
		return 1;
	visit(root);
	preorder(root->left);
	preorder(root->right);
	return 0;
}
int main(void)
{ //二叉树统计字母个数  TODO：统计单词个数，将数值比较换为string compare 
	char str[]={"haabfbbtc"}; 
	tree_t * root=NULL;
	int i=0;
	
	for(i=0;str[i] != 0;i++)
	{
		build_tree(&root,str[i]);// 每个node从root往下找自己的位置	
	}
	preorder(root);
	printf("\n");
	midorder(root);
	printf("\n");
	postorder(root);
	printf("\n"); 
	return 0;
}

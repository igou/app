#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct tree{
struct tree * left;
struct tree * right;
int         value;
}tree_t;
int build_tree(tree_t ** proot,int value){
	tree_t *root=*proot; // point
	tree_t *left,*right;
	
	
	if(!root)
	  {
	  	root = (tree_t *)malloc(sizeof(tree_t));
	  	memset(root,0x00,sizeof(tree_t));
	  	root->value = value;
		printf("malloc\n");
	   }
	else
	{
		if(value<root->value){
			if(root->left == NULL){
			left= (tree_t *)malloc(sizeof(tree_t));
			memset(left,0x00,sizeof(tree_t));
			root->left = left;
			left->value = value;
				printf("world\n");}
			else{
			build_tree(&root->left,value);}
		}
		else if(value>root->value){
			if(root->right == NULL){
			right = (tree_t *)malloc(sizeof(tree_t));
			memset(right,0x00,sizeof(tree_t));
			root->right = right;
			right->value = value;
			}
			else{
			build_tree(&root->right,value);}
		}		
}
*proot=root;
return 0;
}

int main(void)
{
	tree_t * root=NULL;
	build_tree(&root,5);
	build_tree(&root,7);
	build_tree(&root,3);
	printf("xxxxxx %d %d %d",root->value,root->right->value,root->left->value);
	return 0;
}

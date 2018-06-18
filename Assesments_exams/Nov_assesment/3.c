#include<stdio.h>
#include<stdlib.h>
struct bst
{
	int val;
	struct bst *left,*right;
};
void insert(struct bst**node,int data)
{
	struct bst *nu;
	if(*node==NULL)
	{
		nu=malloc(sizeof(struct bst));
		nu->val=data;
		nu->left=NULL;
		nu->right=NULL;
		*node=nu;
	}
	else if(data<(*node)->val)
		insert(&((*node)->left),data);
	else if(data >(*node)->val)
		insert(&((*node)->right),data);
	else
		printf("duplicates are not allowed\n");
}
void print(struct bst *node)
{
	if(node)
	{
		printf("%d-->",node->val);
		print(node->left);
		}
	printf("\n");
	}
	
int main()
{
	int choice;
	int data;
	struct bst *root=NULL,*ptr=NULL;
	while(1)
	{
		printf("1:insert 2:printin \n");
		printf("enter ur choice");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:printf("enter the val");
			       scanf("%d",&data);
			       insert(&root,data);
			       break;
			case 2:print(root);
			       break;
			default:printf("invalid choice\n");
		}
	}
return 0;
}

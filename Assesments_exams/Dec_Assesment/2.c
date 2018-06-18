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
void printin(struct bst *node)
{
	if(node)
	{
		printin(node->left);
		printf("%d-->",node->val);
		printin(node->right);
	}
	
}
void printpre(struct bst *node)
{
	if(node)
	{
		printf("%d-->",node->val);
		printpre(node->left);
		printpre(node->right);
	}
	
}
void printpost(struct bst *node)
{
	if(node)
	{
		printpost(node->left);
		printpost(node->right);
		printf("%d-->",node->val);
	}
	
}
int main()
{
	int choice;
	int data;
	struct bst *root=NULL,*ptr=NULL;
	insert(&root,8);
	insert(&root,4);
	insert(&root,12);
	insert(&root,2);
	insert(&root,5);
	insert(&root,9);
	insert(&root,14);
	insert(&root,3);
	insert(&root,7);
	insert(&root,10);
	
	while(1)
	{
		printf("\n1:printin 2:printpre 3:printpost 4:quit\n");
		printf("enter ur choice");
		scanf("%d",&choice);
		
		switch(choice)
		{
		 	      
			case 1:printin(root);
			       break;
			case 2:printpre(root);
			       break;
			case 3:printpost(root);
			       break;
			case 4:return 0;
			
			default:printf("invalid choice\n");
		}
	}
	return 0;
}

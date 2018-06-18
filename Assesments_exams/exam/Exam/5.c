#include<stdio.h>
#include<stdlib.h>
struct bst
{
	struct bst *left;
	int data;
	struct bst *right;

};
void insert(struct bst **node,int data)
{
	struct bst *nu;
	if(*node==NULL)
	{
		nu=malloc(sizeof(struct bst));
		nu->data=data;
		nu->left=NULL;
		nu->right=NULL;
		*node=nu;

	}
	else
	{
		if(data<(*node)->data)
		insert(&(*node)->left,data);
		else if(data>(*node)->data)
			insert(&(*node)->right,data);

	}
}
void preorder(struct bst *root)
{
	if(root)
	{
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void postorder(struct bst *root)
{
	if(root)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ",root->data);
	}
}
void inorder(struct bst *root)
{
	if(root)
	{
		inorder(root->left);
		printf("%d ",root->data);
		inorder(root->right);
	}
}
int main()
{
	struct bst *root=NULL;
        int n,i=0,data;
	printf("enter no.of elements:");
	scanf("%d",&n);
        printf("please enter values is the form of BST tree only\n");
        while(i<n)
        {
                printf("enter data:");
                scanf("%d",&data);
                insert(&root,data);
                i++;
        }
	printf("preorder:");
        preorder(root);
	printf("\n");
	printf("inorder:");
	inorder(root);	
	printf("\n");
	printf("postorder:");
	postorder(root);
	printf("\n");

}

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
void print_leaf(struct bst *root)
{
	if(root==NULL)
		return;
	if((root->left==NULL)&&(root->right==NULL))
	{
		printf("%d ",root->data);
		return;
	}
	print_leaf(root->left);
	print_leaf(root->right);


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
	printf("leaf nodes are:");
	print_leaf(root);
	printf("\n");
}

#include<stdio.h>
#include<stdlib.h>
typedef struct stack{
	int data;
	struct stack *next;

}NODE;
void add(NODE **head,int num)
{
	int v=0,data;
	NODE *nu,*temp;
	while(v<num)
	{
		nu=malloc(sizeof(NODE));
		printf("enter data:");
		scanf("%d",&nu->data);
		nu->next=NULL;
		if(*head==NULL)
			*head=nu;
		else
		{
			temp=*head;
			while(temp->next)
				temp=temp->next;
			temp->next=nu;
		}
		v++;
	}
}
void print_mid(NODE *head)
{
	NODE *fast,*slow;
	fast=slow=head;
	while((fast->next!=NULL)&&(fast->next->next!=NULL))
	{
		fast=fast->next->next;
		slow=slow->next;
	}
	if(fast->next==NULL)
		printf("mid node value is:%d\n",slow->data);
	else
		printf("mid values are:%d, %d\n",slow->data,slow->next->data);
}
int main()
{
	NODE *head=NULL;
	int num;
	printf("enter no.of nodes to be added:");
	scanf("%d",&num);
	add(&head,num);	
	print_mid(head);

}

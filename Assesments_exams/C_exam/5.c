#include<stdio.h>
#include<stdlib.h>
typedef struct sll
{
	int data;
	struct sll *next;

}NODE;
void insert(NODE **head)
{
	
	NODE *nu,*temp;
	nu=malloc(sizeof(NODE));
	printf("enter data:");
	scanf("%d",&(nu->data));
	nu->next=NULL;
	if(*head==NULL)
	{
		*head=nu;
	}
	else
	{
		temp=*head;
		while(temp->next)
			temp=temp->next;
		temp->next=nu;
	}
}
void print(NODE *head)
{
	if(head!=NULL)
	while(head)
	{
		printf("%d ",head->data);
		head=head->next;
	}
	else
		puts("Empty");

}
void merge(NODE **head1,NODE **head2)
{
	NODE *temp1,*prev1,*temp2,*prev2,*nu;
	temp1=*head1;
	temp2=*head2;
	prev1=*head1;
	while((prev1->next)&&(prev2->next))
	{
		prev1=temp1->next;
		nu=malloc(sizeof(NODE));
		nu->data=temp2->data;
		temp1->next=nu;
		nu->next=prev1;
		prev2=temp2->next;
		*head2=prev2;
		free(temp2);
		temp2=NULL;
		temp2=prev2;
		temp1=prev1;
		
	}
	if(prev1->next==NULL)
	{
		nu=malloc(sizeof(NODE));
		nu->data=temp2->data;
		nu->next=NULL;
		prev1->next=nu;
		prev2=temp2->next;
		*head2=prev2;
		free(temp2);
		temp2=NULL;
		
	}

}
int main()
{
	int n1,n2;
	printf("enter no.of elements in list1,list2:");
	scanf("%d%d",&n1,&n2);
	NODE *head1=NULL,*head2=NULL;
	printf("insert elements into head1:\n");
	while(n1>0)
	{
		insert(&head1);	
		n1--;
	}
	printf("insert elements into head2:\n");
	while(n2>0)
	{
		insert(&head2);	
		n2--;
	}
	merge(&head1,&head2);
	printf("head1:");
	print(head1);
	printf("\n");
	printf("head2:");
	print(head2);
	printf("\n");


}


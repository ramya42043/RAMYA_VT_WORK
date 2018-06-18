#include<stdio.h>
#include<stdlib.h>
typedef struct ll
{
	int data;
	struct ll *next;

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

int search(NODE *head,int data)
{
	NODE *prev = NULL;
	NODE *current = head;
	int count =1;
	while(head != NULL)
	{
			if(head->data == data)
			{
				if(prev != NULL)
				{
				prev->next = current->next;
				current->next = head;
				head = current;
				}
			return count;		
			}
				
		prev = current;
		current = current->next;
		count ++;
	}	
}			

int main()
{
	int n1,search_data;
	printf("enter no.of elements in list:");
	scanf("%d",&n1);
	NODE *head1=NULL;
	printf("insert elements into head1:\n");
	while(n1>0)
	{
		insert(&head1);	
		n1--;
	}
	print(head1);
	printf("\n");
	printf("enter search data:");
	scanf("%d",&search_data);
    int res = search(head1,search_data);
    if(res)
	printf("%d found at %d index\n",search_data,res);
	else
	printf("not found\n");
	print(head1);
	printf("\n");
	
	
	
}


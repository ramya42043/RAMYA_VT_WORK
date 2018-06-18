#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}


void findnthnode(struct Node **head_ref,int num)
{
	struct Node* temp = *head_ref;
	int cnt=0;
	while(temp != NULL)
	{
		cnt ++;
		temp = temp->next;
		
	}
	temp = *head_ref;
	while(temp!=NULL)
	{
		if(cnt-- == num)
			printf("from last %dnd node  data is %d\n",num,temp->data);
		temp= temp->next;
	}
}
 

void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main()
{
    
    struct Node* head = NULL;
 
    push(&head, 7);
    push(&head, 1);
    push(&head, 3);
    push(&head, 2);
 
    puts("Created Linked List: ");
    printList(head);
    printf("\n");
    int node_num;
    printf("enter node number:");
    scanf("%d",&node_num);
    findnthnode(&head, node_num);
    return 0;
}

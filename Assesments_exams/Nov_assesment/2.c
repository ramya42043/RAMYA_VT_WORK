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
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
}
struct Node* reverse(struct Node *temp)
{
	struct Node *head = temp;
	if(!temp)
		return NULL;
	if(temp->next)
	{
	head= reverse(temp->next);
	temp->next->next = temp;
	temp->next = NULL;
	return head;
	}
	else
	return temp;
}
	
int main()
{
    
    struct Node* head = NULL;
    push(&head, 4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
 
    puts("Created Linked List: ");
    printList(head);
    printf("\n");
    head = reverse(head);
    printf("reverse of linked list:\n");
    printList(head);
    printf("\n");
    return 0;
}

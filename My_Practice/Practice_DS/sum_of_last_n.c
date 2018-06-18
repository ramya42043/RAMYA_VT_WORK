#include <stdio.h>
#include<stdlib.h>
 
struct Node {
    int data;
    struct Node* next;
};
 
void push(struct Node** head_ref, int new_data)
{

    struct Node* new_node = malloc(sizeof(struct Node));
 
    new_node->data = new_data;
 
    new_node->next = (*head_ref);
 
    (*head_ref) = new_node;
}
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
} 
void reverseList(struct Node** head_ref)
{
    struct Node* current, *prev, *next;
    current = *head_ref;
    prev = NULL;
 
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
 
    *head_ref = prev;
}
 
int sumOfLastN_NodesUtil(struct Node* head, int n)
{
    if (n <= 0)
        return 0;
 
    reverseList(&head);
 
    int sum = 0;
    struct Node* current = head;
 
    while (current != NULL && n--) {
 
        sum += current->data;
 
        current = current->next;
    }
 
    reverseList(&head);
 
    return sum;
}
 
int main()
{
    struct Node* head = NULL;
 
    push(&head, 12);
    push(&head, 4);
    push(&head, 8);
    push(&head, 6);
    push(&head, 10);
    printList(head);
    int n;
    printf("enter n value:");
    scanf("%d",&n); 
    int res = sumOfLastN_NodesUtil(head, n);
    printf("Sum of last %d nodes = %d\n",n,res);  
    return 0;
}

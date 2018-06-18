#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<stdlib.h>

struct node
{
	int data;
	unsigned int refcount;
	struct node *link;
};


struct node *self_organize(struct node *head,int data)
{
	struct node *temp = head,*prev,*point_node;
	int ref = 0;
	if (head && (head -> data == data)) {
		(head->refcount)++;
		return head;
	}
	while (temp) {
		prev = temp;
		temp = temp -> link;
		if (temp && (temp -> data == data)) {
			point_node = temp;
			ref = ++(temp -> refcount);
			prev->link = temp->link;
			temp = head;
			while (temp && (temp -> refcount) > ref) {
				prev = temp;
				temp = temp ->link;
			}
			if (temp == head)  {
				if (point_node != head) {
					point_node -> link = head;
					head = point_node;
				}
			} else {
				point_node->link = prev -> link;
				prev->link = point_node;
			}
			break;
		}
	}
	return head;
}
struct node *insert(struct node *head, int data)
{
	struct node *newnode = malloc(sizeof(*newnode)),*temp;
	if (!newnode) {
		return (struct node*)-1;
	}

	if (head) {
		temp = head;
		while (temp && temp->link) {
			temp = temp -> link;
		}
		temp -> link = newnode;
	} else {
		head = newnode;
	}
	newnode -> data = data;
	newnode -> link = NULL;
	newnode -> refcount = 0;

	return head;
}


void display(struct node *head)
{
	while (head) {
		//printf("[%d|%d] ->",head->data,head->refcount);
		printf("%d ->",head->data);
		head = head->link;
	}
	printf("\n\n");
}

int main(void)
{
	struct node *head = NULL,*retval;
	int numnodes,data;
	char opt = 'y';
	printf("Enter how many nodes you need\n");
	scanf("%d",&numnodes);
	printf("enter integer data for each node\n");
	while (numnodes) {
		scanf("%d",&data);
		retval = insert(head,data);
		if (retval != (struct node*) -1) {
			head = retval;
		}
		numnodes--;
	}

	printf("\nactual list is\n");
	display(head);
	while (opt == 'y') {
		printf("say 'y' if you want to search value else 'n':  ");
		__fpurge(stdin);
		scanf("%c",&opt);
		if (opt == 'y') {
			printf("enter integer you want to search for:  ");
			scanf("%d",&data);
			head = self_organize(head,data);
		}
	}

	printf("\nself organized list is \n");
	display(head);
	return 0;
}

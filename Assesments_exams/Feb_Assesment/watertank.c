#include<stdio.h>
#include<stdlib.h>

struct node
{
	int tanknum;
	struct node *llink;
	int capacity;
	struct node *rlink;
};

int total = 0;
int lvalue = 0;
int rvalue = 0;

void traverse(struct node *root)
{
	if (root) {
		traverse(root->rlink);
		traverse(root->llink);
		if (root->rlink) {
			rvalue += root->rlink->capacity;
		}
		if (root->llink) {
			lvalue += root->llink->capacity;
		}
	}
}
int main(void)
{
	int test;
	scanf("%d",&test);
	while(test) {
		int ntanks,stank,ind=0,u,v;
		scanf("%d%d",&ntanks,&stank);

		struct node *tanks = malloc(sizeof(struct node)*ntanks);

		for (ind = 0; ind < ntanks; ind++) {
			scanf("%d",&(tanks[ind].capacity));
			tanks[ind].tanknum = ind+1;
			tanks[ind].llink = tanks[ind].rlink = NULL;
		}
		
		for (ind = 0; ind < (ntanks-1); ind++) {
			scanf("%d%d",&u,&v);
			if (!(tanks[u-1].rlink)) {
				tanks[u-1].rlink = &tanks[v-1];
			} else {
				tanks[u-1].llink = &tanks[v-1];
			}
		}
		traverse(&tanks[stank-1]);
		total = tanks[stank-1].capacity+((rvalue>lvalue)?(2*rvalue):(2*lvalue));
		printf("total %d \n",total);
		test--;
	}
	return 0;
}

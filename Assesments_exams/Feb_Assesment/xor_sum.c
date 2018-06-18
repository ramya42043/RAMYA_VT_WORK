#include<stdio.h>
#define MAX_SIZE 100000
int main(void)
{
	int arr[MAX_SIZE],test,num_values,ind_i,ind_j;
	long long int result = 0;
	scanf("%d",&test);
	while (test) {
		scanf("%d",&num_values);
		for (ind_i = 0; ind_i < num_values; ind_i++) {
			scanf("%d",&arr[ind_i]);
		}
		for (ind_i = 0; ind_i < (num_values-1); ind_i++) {
			for (ind_j = ind_i+1; ind_j < num_values; ind_j++) {
				result += (arr[ind_i] ^ arr[ind_j]);
			}
		}
		printf("result is %lld\n",result);
		result = 0;
		test--;
	}
	return 0;
}

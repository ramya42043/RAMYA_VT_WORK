#include <stdio.h>
#include <stdlib.h>

int main() {
  int c, n;
 
	//srand(getpid());
  for (c = 1; c <= 10; c++) {
    n = rand()%50+50 ;
    printf("%d\n", n);
  }
 
  return 0;
}

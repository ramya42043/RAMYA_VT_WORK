#include<stdio.h> 
float plus(float a, float b) { return a+b; }
float minus(float a, float b) { return a-b; }
float times(float a, float b) { return a*b; }
float divide(float a, float b) { return a/b; }
 
int main() {
int a,b;
printf("enter a,b:");
scanf("%d %d",&a,&b);
int res;
 
//declare function pointers
 
  float(*fptr_p)(float, float);
  float(*fptr_m)(float, float);
  float(*fptr_t)(float, float);
  float(*fptr_d)(float, float);
 
//point ptr's to functions
 
  fptr_p=&plus;
  res= (*fptr_p)(a,b);
  printf("sum is %d\n",res);
  fptr_m=&minus;
  res= (*fptr_m)(a,b);
  printf("sub is %d\n",res);
  fptr_t=&times;
  res= (*fptr_t)(a,b);
  printf("mul is %d\n",res);
  fptr_d=&divide;
  res= (*fptr_d)(a,b);
  printf("div is %d\n",res);
 
return 0;
}

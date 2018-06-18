#include<stdio.h> 
  
 void f(); 
  
 int main() 
 { 
 int i; 
 i=20; 
 printf("\n i = %d \n", i); 
 f(); 
 printf("\n i = %d \n", i); 
 return 0; 
 } 
  
 void f() 
 { 
 int j=20; 
 int* a = &j;
printf("%d %d",a,a+8);
 *(a)+=7; 
 }

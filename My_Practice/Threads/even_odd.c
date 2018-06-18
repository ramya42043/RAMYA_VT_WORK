#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <stdlib.h>
int i=0;
void *odd_thread(void *arg);
void *even_thread(void *arg);
main()
{
  int res;
  void *thread_result;
  pthread_t a,b;
  res = pthread_create(&a, NULL, even_thread, NULL);
  if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
  res= pthread_create(&b, NULL, odd_thread, NULL);
   if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
 res = pthread_join(a, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
 printf("even thread is joined\n");
 res=pthread_join(b, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
 printf("odd thread is joined\n");

}

void *even_thread(void *arg) {
    while(i<=10)
     {
       if(i%2==0)
       {
         printf("%d ",i);
         i++;
       }
//	sleep(0.1);
     }
pthread_exit("Bye");
}
void *odd_thread(void *arg) {
    while(i<10)
     {
       if(i%2==1)
       {
         printf("%d ",i);
         i++;
      }
 //      sleep(0.1);
     }
  sleep(1);
 pthread_exit("bye");
}

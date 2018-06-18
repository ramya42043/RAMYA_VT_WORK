#include<stdio.h>
void f(void (*a)()) {
    a();
}

void test() {
    printf("hello world\n");
}

int main() {
     f(&test);
     return 0;
}

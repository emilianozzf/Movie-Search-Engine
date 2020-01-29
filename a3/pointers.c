#include<stdio.h>

void PointerTest() {
    // allocate three integers and two pointers
    int a = 1;
    int b = 2;
    int c = 3;
    int* p;
    int* q;

    // set p to refer to a
    p = &a;
    // set q to refer to b
    q = &b;

    printf("1, %d\n", a); // 1
    printf("2, %d\n", b); // 2
    printf("3, %d\n", c); // 3
    printf("1, %d\n", *p); // 1 
    printf("2, %d\n", *q); // 2

    // mix things up a bit...
    c = *p; // retrieve p's pointee value (1) and put it in c
    p = q; // change p to share with q (p's pointee is now b)
    *p = 13; // dereference p to set its pointee (b) to 13 (*q is now 13)
    
    printf("1, %d\n", a); // 1
    printf("13, %d\n", b); // 13
    printf("1, %d\n", c); // 1
    printf("13, %d\n", *p); // 13 
    printf("13, %d\n", *q); // 13
}

int main() {
    PointerTest();
    return 0;
}

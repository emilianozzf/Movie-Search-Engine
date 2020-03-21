// Write a C program that swaps two integers in a function

#include <stdio.h>

void swap(int* a, int* b) { // a,b are addresses
  int tmp = *a; // save the value at the address a
  *a = *b; // put the value at address b in the address a
  *b = tmp; // put the saved value in address b
}



int main() {
  int x = 5;
  int y = 10;
  printf("x: %d, y: %d\n", x, y);
  swap(&x, &y);
  printf("x: %d, y: %d\n", x, y);
}

// Write a C program that swaps two integers(in the main body of code).
#include <stdio.h>

int main() {
  long x = 5;
  long y = 42;
  printf("x: %d, y: %d\n", x, y);
  long tmp = x;
  x = y; 
  y = tmp; 
  printf("x: %d, y: %d\n", x, y);
}

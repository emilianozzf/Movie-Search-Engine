// Write a C program that swaps two integers(in the main body of code).
#include <stdio.h>

int main() {
  int x = 5;
  int y = 42;
  printf("x: %d, y: %d\n", x, y);
  int tmp = x;
  x = y; 
  y = tmp; 
  printf("x: %d, y: %d\n", x, y);
}

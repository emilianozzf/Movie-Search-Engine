// Write a C program called array2.c that has an array of 400 integers in the function of main that is dynamically allocated.
#include <stdlib.h>

int main() {
  int* my_array = (int*) malloc(400 * sizeof(int));
  my_array[0] = 72;
  my_array[70] = 56;
  free(my_array);
  return 0;
}


#include <stdio.h>
#include "sort.h"


int main() {
    int const kSize = 32;
    int arr[kSize];

    for (int i = 0; i < kSize; i++) {
        arr[i] = kSize - i;
    }

    printf("The unsorted array of ints: ");
    for (int i = 0; i < kSize; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    Sort(arr, kSize);

    printf("The sorted array of ints: ");
    for (int i = 0; i < kSize; i++) {
    printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

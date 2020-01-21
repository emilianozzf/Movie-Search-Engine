#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"


int main() {
    srand(time(0));

    const int kMinVal = 1;
    const int kMaxVal = 32;
    int arr[kMaxVal];

    for (int i = 0; i < kMaxVal; i++) {
        arr[i] = kMinVal + (rand() % (kMaxVal - kMinVal + 1));
    }

    printf("The unsorted array of ints: ");
    for (int i = 0; i < kMaxVal; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    Sort(arr, kMaxVal);

    printf("The sorted array of ints: ");
    for (int i = 0; i < kMaxVal; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

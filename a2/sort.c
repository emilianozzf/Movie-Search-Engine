#include <stdio.h>

void Sort(int* array, int length) {
	int left = length / 2;
	int count = 0;
	while (left > 0) {
		int q = length / 2;
		int r = 0;
		int gap = left;
		while (q >= left) {
			for (int i = 0; i < length - gap; i++) {
				if ((i & left) == r) {
					count += 1;
					if (array[i] > array[i+gap]) {
						int tmp = array[i];
						array[i] = array[i+gap];
						array[i+gap] = tmp;
					}
				}
			}
			gap = q - left;
			q = q / 2;
			r = left;
		}
		left = left / 2;
	}
	printf("The number of comparisons: %d\n", count);
}

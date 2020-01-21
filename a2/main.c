#include <stdio.h>
#include "sort.h"


int main() {
	int size = 1048576;
	int arr[size];

	for (int i = 0; i < size; i++){
		arr[i] = size - i;
	}
	
	//printf("The unsorted array of ints: ");
	//for (int i = 0; i < size; i++) {
	//	printf("%d ", arr[i]);
	//}
	//printf("\n");
	
	Sort(arr, size);
	
	//printf("The sorted array of ints: ");
	//for (int i = 0; i < size; i++) {
	//	printf("%d ", arr[i]);
	//}
	//printf("\n");
		
	return 0;	
}

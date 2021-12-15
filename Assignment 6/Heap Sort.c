#include <stdio.h>
#include <stdlib.h>
/** Function: swap
 * ---------------------
 * Swaps 2 numbers in memory
 * 
 * a: Address of the first number
 * b: Address of the second number
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/** Function: display
 * ---------------------
 * Displays the elements of an array
 * 
 * array: Array to display
 * n: Length of the array
 */
void display(int array[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", array[i]);
}

/** Function: MAX_HEAPIFY
 * ------------------------
 * Heapifies a given array 
 * 
 * array: Array to heapify
 * i: Position of the root of the heap
 * n: Length of the array
 */
void MAX_HEAPIFY(int array[], int i, int n) {
    int left = (2 * i) + 1; // position of left child
    int right = (2 * i) + 2;// position of right child
    int largest = i;
    if(left < n && array[left] > array[i])
        largest = left;
    if(right < n && array[right] > array[largest])
        largest = right;
    if (largest != i) { // heapify if nodes have moved
        swap(&array[i], &array[largest]);
        MAX_HEAPIFY(array, largest, n);
    }
}

/** Function: BUILD_MAX_HEAP
 * ---------------------
 * Builds a max heap from a given array
 * 
 * array: Array to be made a heap
 * n: Length of the array
 */
void BUILD_MAX_HEAP(int array[], int n) {
    // final half of the array contains leaf nodes
    for(int i = (int)(n/2)+1; i >= 0; i--)
        MAX_HEAPIFY(array, i, n);
}

void heapSort(int array[], int n) {
    // turn the input array into a heap
    BUILD_MAX_HEAP(array, n);
    for (int i = n - 1; i >= 0; i--) {
        // move the root of the heap to the end of the array
        swap(&array[0], &array[i]);
        // heapify the array excluding the elements swapped to end
        MAX_HEAPIFY(array, 0, i);
    }
}

int main() {
    int n;
    scanf("%d", &n);    // accept array length
    if(n < 1) { // Input validation
        printf("INVALID INPUT");
        exit(0);
    }
    int array[n];
    for(int i = 0; i < n; i++)  // accept the array elements
        scanf("%d", &array[i]);
    heapSort(array, n);
    display(array, n);
}
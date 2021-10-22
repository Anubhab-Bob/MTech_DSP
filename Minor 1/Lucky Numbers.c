#include <stdio.h>
#include <stdlib.h>

/** Function: createArray
 * ----------------------
 *  Creates an array of given size having 1 to size elements
 * 
 * n: Size of the array
 * 
 * returns: Address of the newly created array
 */
int *createArray(int n) {
	int *array = (int*)malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		array[i] = i + 1;
	return array;
}

/** Function: getNextLength
 * ----------------------
 *  Gives the length of the next array to create
 * 
 * length: Size of the current array
 * skip: Number of elements to jump
 * 
 * returns: Length of the neww array to create
 */
int getNextLength(int length, int skip) {
	int multiples = (int)(length / skip);
	return (length - multiples);
}

/** Function: getNextArray
 * ----------------------
 *  Gives the the next array containing skipped elements
 * 
 * array: The current array
 * oldLength: Size of the current array
 * newLength: Size of the new array
 * skip: Number of elements to jump
 * 
 * returns: Length of the neww array to create
 */
int *getNextArray(int *array, int oldLength, int newLength, int skip) {
	int *nextArray = (int*)malloc(sizeof(int) * newLength);
	int jump = skip - 1;	// index starts from 0
	for(int i = 0, j = 0; j < oldLength; j++) {
		if(j != jump)
			nextArray[i++] = array[j];
		else
			jump += skip;
	}		
	free(array);	// deallocate memory from original array
	
	return nextArray;
}

/** Function: displayArray
 * ----------------------
 *  Prints the elements of a given array
 * 
 * array: The array to display
 * length: Size of the array
 * 
 * returns: Length of the neww array to create
 */
void displayArray(int *array, int length) {
	for(int i = 0; i < length; i++)
		printf("%d ", array[i]);
}

int main() {
	int n;
	scanf("%d", &n);
	if(n <= 0) {  // terminate program if input is invalid
		printf("INVALID INPUT");
		return 1;
	}
	int *array = createArray(n);
	for(int skip = 2; skip <= n; skip++) {
		int nextLength = getNextLength(n, skip);
		array = getNextArray(array, n, nextLength, skip);
		n = nextLength;
	}
	displayArray(array, n);
}

#include <stdio.h>
#include <stdlib.h>

#define BASE 10

/** Structure: node
 * --------------------
 *  A data structure to store generic data for a singly linked list
 * 
 */
struct node {
    void *data;
    struct node *next;
};

typedef struct node node;

/** Structure: list
 * --------------------
 *  A data structure to store a singly linked list
 * 
 */
struct list
{
    node *head;
    node *tail;
    int size;
};

typedef struct list list;

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to given integer value
 * 
 * data: Element to be inserted in list
 * 
 * returns: Address of the newly created node
 */
node* createNode(void *data) {
	node *tmp = (node*)malloc(sizeof(node));
    tmp->data = data; 
    tmp->next = NULL;
    
    return tmp;
}

/** Function: createList
 * ----------------------
 *  Creates a blank singly linked list
 * 
 * data: Element to be inserted in list
 * 
 * returns: Address of the newly created node
 */
list * createList()
{
    list *l = malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    
    return l;
}

/** Function: inputArray
 * ----------------------
 *  Fills an integer array with inputs and gives the maximum number of 
 *  digits in any number in the array
 * 
 * inp: Address of the array in which to insert the inputs
 * length: Length of inp
 * 
 * returns: Maximum number of digits in the largest value in inp
 */
int inputArray(int **inp, int length) {
    int maxDigits = 0;
    *inp = (int*)malloc(sizeof(int) * length);
    for(int i = 0; i < length; i++) {
        scanf("%d", ((*inp)+i));
        int tmp = *((*inp) + i);
        if(tmp < 0)
            return 0;
        int size = 0;
        while(tmp) {    // count number of digits in the input value
            tmp /= 10;
            size++;
        }
        if(size > maxDigits)
            maxDigits = size;
    }
    
    return maxDigits;
}

/** Function: insertLast
 * ----------------------
 *  Inserts a new node at the end of a given linked list
 * 
 * l: Address of the pointer to the linked list
 * data: The new generic value to be inserted
 */
void insertLast(list *l, void *data) {
    node *newNode = createNode(data);
    if (l->head == NULL) {  // list is empty
        l->head = newNode;
        l->tail = newNode;
        l->size = 1;
        return;
    }
    l->tail->next = newNode;
    l->tail = l->tail->next;
    l->size++;
}

/** Function: removeFirst
 * ----------------------
 *  Deletes a node from the beginning of a given linked list
 * 
 * l: Address of the pointer to the linked list.
 *      l must not be null.
 * 
 * returns: The deleted value
 */
void* removeFirst(list *l) {
	void *removed = l->head->data;
	node *tmp = l->head;
	l->head = l->head->next;
	l->size--;
    free(tmp);
    if(l->size < 1) {   // reset list if empty
        l->head = NULL;
        l->head = NULL;
    }
    
    return removed;
}

/** Function: isEmpty
 * ----------------------
 *  Checks if a given list is empty
 *
 *  l: Address of a linked list
 *
 *  returns: 1 if l is empty, 0 otherwise
 */
int isEmpty(list *l)
{
    if(l->size == 0)
        return 1;
    return 0;
}

/** Function: extractDigit
 * ----------------------
 *  Extracts the digit from a given place of a given number
 * 
 * value: Number from which to extract the digit
 * place: Place value of the digit to extract
 * base: base of the number 
 * 
 * returns: The extracted digit
 */
int extractDigit(int value, int place, int base) {
    for(int i = 0; i < place; i++)
    	value /= base;

	return (value % base);
}

/** Function: radixSort
 * ----------------------
 *  Performs radix sort on a given array
 * 
 * a: The array to sort
 * length: Number of elements in a
 * maxDigits: Number of digits in the largest value of a
 * base: base of the numbers used
 */
void radixSort(int a[], int length, int maxDigits, int base){
	list *array[base];
    for(int i = 0; i < BASE; i++)   // initialise the structure pointer array
    	array[i] = createList();
    for(int place = 0; place < maxDigits; place++) {
	    for(int i = 0; i < length; i++) {   // arrange elements from array into lists
	        int index = extractDigit(a[i], place, base);
	        int *n = malloc(sizeof(int)); // allocate data for the void pointer
	        *n = a[i];
	        insertLast(array[index], n);
	    }
	    for(int i = 0, pos = 0; i < BASE; i++) {    // arrange elements from lists into array
	    	while(!isEmpty(array[i])) {
			    int *n = removeFirst(array[i]);
			    a[pos++] = *n;
			    free(n);
			}
		}
	}
	for(int i = 0; i < 10; i++) // free the list array
        free(array[i]);
}

/** Function: displayArray
 * ----------------------
 *  Diplays the elements of a given array
 * 
 * arr: The array whose elements are to be displayed
 * length: Length f the array arr
 */
void displayArray(int *arr, int length) {
	for(int i = 0; i < length; i++)
        printf("%d ", arr[i]);
}

int main() {
    int *input, length;
    scanf("%d", &length);
    if(length <= 0) {
        printf("INVALID INPUT");
        return 1;
    }
    int maxDigits = inputArray(&input, length);
    if(!maxDigits) {
        printf("INVALID INPUT");
        return 1;
    }
    radixSort(input, length, maxDigits, BASE);  // perform radix sort
	displayArray(input, length);    // display the result
}
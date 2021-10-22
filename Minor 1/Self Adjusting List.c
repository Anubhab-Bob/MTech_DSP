#include <stdio.h>
#include <stdlib.h>

/** Structure: node
 * --------------------
 *  A data structure to store data for a singly linked list
 * 
 */
struct node {
    int data;
    struct node *next;
};

typedef struct node node;

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to given integer value
 * 
 * data: Value to be inserted in list
 * 
 * returns: Address of the newly created node
 */
node* createNode(int data) {
	node *tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
	tmp->next = NULL;
    
    return tmp;
}

/** Function: insertFront
 * ----------------------
 *  Inserts a new node at the front of a given linked list
 * 
 * head: Address of the pointer to the linked list
 * data: The new data to be inserted
 */
void insertFront(node **head, int data) {
	node *newNode = createNode(data);
    if (*head == NULL)
        *head = newNode;
    else {
        newNode->next = *head;
        *head = newNode;
    }
}

/** Function: removeFirst
 * ----------------------
 *  Deletes a node from the beginning of a given linked list
 * 
 * head: Address of the pointer to the linked list.
 *      head must not be null.
 * 
 * returns: The deleted value
 */
int removeFirst(node **head) {
	node *tmp = *head;
	*head = tmp->next;
	int removed = tmp->data;
    free(tmp);  // free memory allocated for removed node
    
    return removed;
}

/** Function: Find
 * ----------------------
 *  Finds if a node exists with a given value in a given linked list
 * 
 * head: The list
 * data: The value to find
 * 
 * returns: The index of the value if present, -1 otherwise
 */
int Find(node *head, int data) {
	node *tmp = head;
	int index = 0;
	while(tmp != NULL) {
		if(tmp->data == data)
			return index;   // return index when data is found
		tmp = tmp->next;
		index++;
	}
	return -1;  // return -1 if data is not found
}

/** Function: moveNode
 * ----------------------
 *  Moves a node to the beginning of a given linked list
 * 
 * head: Address of the pointer to the linked list.
 * move: Address of the pointer to the node to move.
 */
void moveNode(node **head, node** move) {
	if(*head == *move)	// node is already at the beginning
		return;
	node *tmp = *head;
	while(tmp->next != *move)   // reach node previous to the one to move
		tmp = tmp->next;
	tmp->next = (*move)->next;
	(*move)->next = *head;
	*head = *move;
}

/** Function: isEmpty
 * ----------------------
 *  Checks if a given linked list is empty
 * 
 * head: The list
 * returns: The 1 if the list is empty, 0 otherwise
 */
int isEmpty(node *head) {
	if(head == NULL)
		return 1;
	return 0;
}

/** Function: freeList
 * ----------------------
 *  Frees all the memory associated with a given linked list
 * 
 * head: Address of the pointer to the linked list to be freed
 */
void freeList(node *head) {
    // all nodes have to be freed
    while(head != NULL) {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
	node *list = NULL;
	int cont = 1;
	while(cont) {
		int choice, data, index;
		node *tmp;
		scanf("%d", &choice);
		switch (choice) {
			case 1 :	scanf("%d", &data);
						insertFront(&list, data);
						break;
			case 2 :	if(isEmpty(list))
							printf("LE ");
						else 
							printf("%d ", removeFirst(&list));
						break;
			case 3 :	scanf("%d", &data);
						index = Find(list, data);
						if(index == -1) {
							printf("ENF ");
							break;
						}
						printf("%d ", index);
						tmp = list;
						while (index) {
							tmp = tmp->next;
							index--;
						}
						moveNode(&list, &tmp);
						break;
			case -1 :	cont = 0;   // reset cont to terminate loop
						freeList(list); // free all memory associated with list
						break;
			default:    cont = 0;   // any invalid input terminates the program
						freeList(list); // free all memory associated with list
						break;
		}
	}
}
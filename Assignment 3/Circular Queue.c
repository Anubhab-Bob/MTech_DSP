#include <stdio.h>
#include <stdlib.h>

/** Structure: queue
 * ------------------
 *  A queue data structure with dynamic capacity
 * 
 */
struct queue {
    int front;
    int rear;
    int size;
    int* data;
};
typedef struct queue queue;

// prototypes of functions used
queue* createQueue(int size);
int getFront(queue* qu);
int getFront(queue* qu);
int isEmpty(queue* qu);
int isFull(queue* qu);
queue* resizeQueue (queue* qu);
void enqueue(queue* qu, int value);
int dequeue(queue *qu);

/** Function: createQueue
 * -----------------------
 *  Creates a queue using struct queue
 * 
 *  size: Capacity of the created queue
 *  returns: Address of the created queue
 */
queue* createQueue(int size) {
    queue *qu = (queue*) malloc(sizeof(queue));
    qu->front = -1;
    qu->rear = -1;
    qu->size = size;
    qu->data = (int*)malloc(sizeof(int) * qu->size);
    
    return qu;
}

/** Function: getFront
 * -----------------------
 *  Returns the element at the front of the given queue
 * 
 *  qu: Queue whose front element is to be viewed
 *  returns: Element at the front of qu
 */
int getFront(queue *qu) {
    return qu->data[qu->front];
}

/** Function: isEmpty
 * -----------------------
 *  Checks if the given queue is empty
 * 
 *  qu: Queue which is to be checked for emptiness
 *  returns: 1 if qu is empty, 0 otherwise
 */
int isEmpty(queue *qu) {
    if (qu->front < 0)
        return 1;
    return 0;
}

/** Function: isFull
 * -----------------------
 *  Checks if the given queue is full
 * 
 *  qu: Queue which is to be checked if full
 *  returns: 1 if qu is full, 0 otherwise
 */
int isFull(queue *qu) {
    if(qu->front == (qu->rear + 1) % qu->size)
        return 1;
    return 0;
}

/** Function: resizeQueue
 * -----------------------
 *  Doubles a given queue
 * 
 *  qu: Queue which is to be doubled
 *  returns: Address of the queue after being doubled
 */
queue* resizeQueue (queue *qu) {
    queue *newQ = createQueue(qu->size * 2);    // create new queue with double capacity
    int i = qu->size;
    while (i) {     // copy elements in the previous queue to new queue
        enqueue(newQ, dequeue(qu));
        i--;
    }
   
    free(qu);   // deallocate the previous queue
    
    return newQ;
}

/** Function: enqueue
 * -----------------------
 *  Inserts the given value into a given queue
 * 
 *  qu: Queue in which to be inserted
 *  value: Value to be inserted into qu
 */
void enqueue (queue *qu, int value) {
    qu->rear = (qu->rear + 1) % qu->size;
    qu->data[qu->rear] = value;
    if(qu->front < 0)
        qu->front++;
}

/** Function: dequeue
 * -----------------------
 *  Deletes the front element from a given queue
 * 
 *  qu: Queue from which to be deleted
 *  returns: Value removed from the queue
 */
int dequeue (queue*qu) {
    int removed = qu->data[qu->front];
    qu->front = (qu->front + 1) % qu->size;
    
    if(qu->front == ((qu->rear + 1) % qu->size)) {   // Reset queue if now empty
        qu->front = -1;
        qu->rear = -1;
    }
    
    return removed;
}

/** Function: freeQueue
 * -----------------------
 *  Frees all the memory associated with a given queue
 * 
 *  qu: Queue to be freed
 */
void freeQueue(queue *qu) {
    free(qu->data);
    free(qu);
}

int main() {
    int initialSize = 4;
    queue *q = createQueue(initialSize);  // Initializing with size 4
    int cont = 1;   // Variable to store choice of continuing
    while (cont) {
        int choice;
        int value;
        scanf("%d", &choice);
        switch(choice) {
            case 1 : 
                scanf("%d", &value);
                if(isFull(q)) {
                    printf("QF QSD ");
                    q = resizeQueue(q);
                }
                enqueue(q, value);
                break;
            
            case 2 :
                if(isEmpty(q))
                    printf("QE ");
                else
                    printf("%d ", dequeue(q));
                break;
                
            case 3 :
                if(isEmpty(q))
                    printf("QE ");
                else
                    printf("%d ", getFront(q));
                break;
                
            case -1 :
                cont = 0;   // Reset cont to stop loop
                break;
        }
    }
    
    freeQueue (q);   // Free memory once complete
}

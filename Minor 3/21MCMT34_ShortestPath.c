#include <stdio.h>
#include <stdlib.h>

/** Structure: queue
 * ------------------
 *  A queue data structure
 */
struct queue {
	int rear;
	int front;
	int size;
	int *data;
};

typedef struct queue queue;

/** Function: createQueue
 * -----------------------
 *  Creates an empty queue using struct queue
 * 
 *  size: Capacity of the created queue
 * 
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

/** Function: isEmpty
 * -----------------------
 *  Checks if the given queue is empty
 * 
 *  qu: Queue which is to be checked for emptiness
 * 
 *  returns: 1 if qu is empty, 0 otherwise
 */
int isEmpty(queue *qu) {
    if (qu->front < 0)
        return 1;
    return 0;
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
 * 
 *  returns: Value removed from the queue
 */
int dequeue (queue *qu) {
    int removed = qu->data[qu->front];
    qu->front = (qu->front + 1) % qu->size;
    if(qu->front == ((qu->rear + 1) % qu->size)) { 	// Reset queue if empty
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

/** Function: getIndex
 * -----------------------
 *  Gives the index of a given key in a given array
 * 
 *  arr: Array to be searched
 *  len: Size of arr
 *  key: The value to search
 * 
 *  returns: Index of key in arr if present, -1 otherwise
 */
int getIndex(int *arr, int len, int key) {
	int i;
    for(i = 0; i < len; i++) {
        if(arr[i] == key)
            return i;
    }
    return -1;
}

/** Function: displayArray
 * -----------------------
 *  Displays the elements of a given array
 * 
 *  arr: Array to be searched
 *  len: Size of arr
 */
void displayArray(int arr[], int len) {
	int i;
    for(i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/** Function: getShortestPath
 * -----------------------
 *  Gives the shortest path between 2 given nodes in a graph
 * 
 *	s: The source node from where distance is to be calculated
 *	t: The target node upto which distance is to be calculated
 *  x: The first array in the forward star representation of a graph
 *  y: The second array in the forward star representation of a graph
 *  n: Size of x
 *  m: Size of y
 *
 *  returns: The shortest path length from s to t if path exists,
 *				0 otherwise.
 */
int getShortestPath(int s, int t, int *x, int *y, int n, int m) {
    int visited[n], levels[n];
    int j;
	for(j = 0; j < n; j++) {
		visited[j] = 0;
		levels[j] = -1;
	}
	queue *q = createQueue(n);  // Initializing the queue used in BFS
	enqueue(q, s);	// enqueue the starting vertex
	levels[s] = 0;	// make start node be at level 0
	visited[s] = 1; // mark start node as visited
	do
	{
		int node=dequeue(q);	// get next node from front of queue
		if(node == t) {		// terminate traversal if end is reached
			freeQueue(q);		// free the queue after using
			displayArray(levels, n);
			return levels[t];
		}
		int neighbourCount;
		if(node == (n-1))
		    neighbourCount = m - x[node];
		else
		    neighbourCount = x[node+1] - x[node];
		
		if (neighbourCount < 0)	// node is disconnected
			break;
		    
		printf("\n\nNode = %d\tNeighbours = %d\n", node, neighbourCount);
		int i = x[node];    // starting index of neighbours
		while(neighbourCount) {
			// if a new vertex is reached then enqueue it
			if(!visited[y[i]]) {
			    visited[y[i]] = 1;		// mark the node as visited
			    printf("Reachead = %d\n", y[i]);
				enqueue(q, y[i]);
				// set the level of newly visited node
				levels[y[i]] = levels[node] + 1;	
			}
			i++;
			neighbourCount--;
		}
	}
	while(!isEmpty(q));
	freeQueue(q);	// free the queue after using
	return -1;		// end vertex could not be reached
}

/** Function: takeInput
 * -----------------------
 *  Function to take necessary inputs
 * 
 *	s: The address to store the source node
 *	t: The address to store the target node
 *  x: The base address of the first array in the forward star representation of a graph
 *  y: The base address of the second array in the forward star representation of a graph
 *  n: Size of x
 *  m: Size of y
 *  
 *  returns: 1 if all inputs are valid, 0 otherwise.
 */
int takeInput(int *n, int *m, int *s, int *t, int **x, int **y) {
    scanf("%d", n);
    scanf("%d", m);
    *m = (*m) * 2;	// undirected graph
    if((*n) <= 0 || (*m) <= 0)
    	return 0;
    // arrays for forward star representation
    *x = (int*)malloc(sizeof(int) * (*n));
    *y = (int*)malloc(sizeof(int) * (*m));
    // initialise the arrays
    int i;
    for(i = 0; i < (*n); i++)
        *((*x) + i) = -1;
    for(i = 0; i < (*m); i++)
        *((*y) + i) = -1;
    for(i = 0; i < (*m); i++) {		// take input of edges
        int n1, n2;
        scanf("%d", &n1);
        scanf("%d", &n2);
        if(n1 < 0 || n1 >= (*n) || n2 < 0 || n2 >= (*n)) {    // invalid input
            free(*x);
            free(*y);
            return 0;
        }
        if((*((*x) + n1)) == -1)	// save starting index for current node's neighbours
            (*((*x) + n1)) = i;
        *((*y) + i) = n2;
    }
    scanf("%d", s);
    scanf("%d", t);
    if((*s) < 0 || (*s) >= (*n) || (*t) < 0 || (*t) >= (*n)) {    // invalid input
    	free(*x);
        free(*y);
        return 0;
    }
    return 1;	// all inputs valid
}

int main() {
    //number of nodes, edges, source node, target node
    int n, m, s, t, *x, *y;
    if(!takeInput(&n, &m, &s, &t, &x, &y)) {
        printf("INVALID INPUT");
        exit(0);
    }
    displayArray(x, n);
    displayArray(y, m);
    printf("%d\t%d\n", s, t);
    int distance = getShortestPath(s, t, x, y, n, m);
    if(distance == -1)
        printf("INVALID INPUT");
    else
        printf("%d\n", distance);
    free(x);
    free(y);
}

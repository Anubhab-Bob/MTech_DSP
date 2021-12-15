#include <stdio.h>
#include <stdlib.h>

/** Structure: node
 * ------------------
 *  A node data structure to hold nodes of the adjacency list
 */
struct node
{
	int vertexNum;
	struct node *next;
};
typedef struct node vertex;

/** Structure: list
 * ------------------
 *  A list data structure to hold the adjacency list
 */
struct list
{
	vertex *head;
};
typedef struct list list;

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

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to an operator in the expression
 * 
 *  v: The value to be inserted into the queue
 * 
 *  returns: Address of the newly created node
 */
vertex* createNode(int v) {
    vertex *newNode = (vertex*)malloc(sizeof(vertex));
    newNode->vertexNum = v;
    newNode->next = NULL;
    
    return newNode;
}

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
int dequeue (queue *qu) {
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

/** Function: addNewEdge
 * -----------------------
 *  Adds a new entry into adjacency list corresponding to a new edge
 * 
 * adjList: The adjacency list
 * s: Source vertex of the new edge
 * d: Destination vertex of the new edge
 */
void newEdge(list *adjList[], int s,int d)
{
	vertex *source, *dest, *current;
	source = createNode(s-1);
	dest = createNode(d-1);
	// add destination node to list of source node
	if(adjList[s-1]->head==NULL)	
		adjList[s-1]->head=dest;
	else
	{
		current=adjList[s-1]->head;
		while((current->next!=NULL)&&(current->vertexNum!=d))
			current=current->next;
		if(current->vertexNum!=d)
			current->next=dest;
		else	// edge already added
			free(dest);
	}
	// add source node to list of destination node if not self loop
	if(s == d)
		return;
	if(adjList[d-1]->head==NULL)
		adjList[d-1]->head=source;
	else
	{
		current=adjList[d-1]->head;
		while((current->next!=NULL)&&(current->vertexNum!=s))
			current=current->next;
		if(current->vertexNum!=s)
			current->next=source;
		else	// edge already added
			free(source);		
	}
}

/** Function: bfsTraverse
 * -----------------------
 *  Performs a BFS traversal of a graph represented
 *  using adjacency list starting from a given node
 * 
 *  adj: Adjacency list of the graph
 *  numOfNodes: Number of nodes in the graph
 *  start: starting vertex
 *  visited: Array depicting which vertices are visited
 */
void bfsTraverse(list *adj[], int numOfNodes, int start, int visited[]) {
	queue *q = createQueue(numOfNodes);  // Initializing the queue used in BFS
	enqueue(q, start);	// enqueue the starting vertex
	do
	{
		int node=dequeue(q);
		if(!visited[node]) {
			visited[node] = 1;
			printf("V%d, ", node + 1);
		}
		vertex *current = adj[node]->head;
		while(current != NULL) {
			// if a new vertex is reached then enqueue it
			if(visited[current->vertexNum]==0)
				enqueue(q, current->vertexNum);
			current = current->next;
		}
	}
	while(!isEmpty(q));
	freeQueue(q);	// free the queue after using
}

/** Function: printList
 * -----------------------
 *  Displays the adjacency list of a graph
 *  
 *  adjList: The adjacency list to print
 *  size: Size of the adjacency list
 */
void printList(list *adjList[], int size)
{
	printf("The adjacency list is :");
	for(int i = 0; i < size; i++)
	{
		vertex *current=adjList[i]->head;
		printf("\nV%d ----> ",i + 1);
		while(current)
		{
			printf("V%d, \t",current->vertexNum + 1);
			current=current->next;
		}
	}
}

/** Function: findComponents
 * -----------------------
 *  Gives the components of a graph represented using 
 *  adjacency list by performing BFS traversal
 * 
 *  fileName: The name of the input file
 *  
 *  returns: Number of components in the graph
 */
int findComponents (char *fileName) {
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL) {
		printf("File cannot be accessed!\n");
		return -1;
	}
	int numOfNodes, numOfEdges, n1, n2;
	int components = 0;
	fscanf(fp, "%d", &numOfNodes);// read the number of nodes in the graph
	fscanf(fp, "%d", &numOfEdges);// read the number of edges in the graph
	list *adjList[numOfNodes];	// the adjacency list declaration
	for(int i=0;i<numOfNodes;i++) {
		adjList[i]=(list*)malloc(sizeof(list));
		adjList[i]->head=NULL;
	}
	while(numOfEdges) {
		fscanf(fp, "%d %d", &n1, &n2);
		if(((n1>0)&&(n1<=numOfNodes))&&(n2<=numOfNodes)&&(n2>0))
			newEdge(adjList, n1, n2);	// add valid edge to list
		else {
			printf("Graph input contains errors.");
			return -1;
		}
		numOfEdges--;
	}	
	fclose(fp);	// close file after input is read
	printList(adjList, numOfNodes);
	int visited[numOfNodes];	// array of visited vertices
	for(int i = 0; i < numOfNodes; i++) 
		visited[i] = 0;
		
	for(int i = 0; i < numOfNodes; i++) {
		if(visited[i] == 0) {
			components++;
			printf("\nComponent %d --> ", components);
			bfsTraverse(adjList, numOfNodes, i, visited);
		}
	}
	return components;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Wrong number of arguments!\n");
		exit(0);
	}
	int components = findComponents(argv[1]);
	if(components != -1)
		printf("\nNumber of Components = %d\n", components);
}
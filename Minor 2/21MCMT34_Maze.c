#include <stdio.h>
#include <stdlib.h>
#define DIM 12		// maximum dimension of the maze

/** Structure: node
 * ------------------
 *  A node data structure to hold nodes of the adjacency list
 */
struct node
{
	int vertexNum;		// vertex id
	int rowIdx;			// corresponding row
	int colIdx;			// corresponding column
	struct node *next;
};

typedef struct node vertex;

/** Structure: list
 * ------------------
 *  A list data structure to hold the adjacency list of a graph
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
 *  v: The vertex to be inserted into the queue
 *  r: The corresponding row of v
 *  c: The correpsonding column of c
 * 
 *  returns: Address of the newly created node
 */
vertex* createNode(int v, int r, int c) {
    vertex *newNode = (vertex*)malloc(sizeof(vertex));
    newNode->vertexNum = v;
    newNode->rowIdx = r;
    newNode->colIdx = c;
    newNode->next = NULL;
    
    return newNode;
}

/** Function: createQueue
 * -----------------------
 *  Creates an empty queue using struct queue
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

/** Function: mapNode
 * -----------------------
 *  Maps a node to a vertex number if not already mapped.
 *  If node is mapped then the corresponding vertex number is returned.
 * 
 *  adjList: The adjacency list of nodes of a graph
 *  nodes: Number of nodes in the graph
 *  r: Row number of the given vertex
 *  c: Column number of the given vertex
 *
 *  returns: Vertex number of the given node.
 */
int mapNode(list *adjList[], int nodes, int r, int c, int cur) {
	int i;
	for(i = 0; i < nodes; i++)
	{
		vertex *current=adjList[i]->head;
		if(current == NULL) {		// unassigned vertex number found
			// a previously found pendent vertex will also have current = NULL
			if(i > cur)		// make sure it is not an existing pendent vertex
				return i;
			continue;
		}
		while(current != NULL) {	// check for availability of given vertex
			if(current->rowIdx == r && current->colIdx == c)
				return current->vertexNum;
			current=current->next;
		}
	}
}

/** Function: addNewEdge
 * -----------------------
 *  Adds a new entry into adjacency list corresponding to a new edge.
 *  Since the edges are undirected, each pair of vertices will have
 *  2 entries in the adjacency list considering the same edge.
 *
 * adjList: The adjacency list of the graph
 * s: Source vertex of the new edge
 * r1: Row number of s
 * c1: Column number of s
 * d: Destination vertex of the new edge
 * r2: Row number of d
 * c2: Column number of d
 */
void addNewEdge(list *adjList[], int s, int r1, int c1, int d, int r2, int c2) {
	vertex *source, *dest, *current;
	source = createNode(s, r1, c1);
	dest = createNode(d, r2, c2);
	// add destination node to list of source node
	if(adjList[s]->head==NULL)	
		adjList[s]->head=dest;
	else {
		current=adjList[s]->head;
		while((current->next!=NULL)&&(current->vertexNum!=d))
			current=current->next;
		if(current->vertexNum!=d)
			current->next=dest;
		else	// edge already exists
			free(dest);
	}
	// add source node to list of destination node if not self loop
	if(s == d)	// but situation unlikely in given problem
		return;
	if(adjList[d]->head==NULL)
		adjList[d]->head=source;
	else {
		current=adjList[d]->head;
		while((current->next!=NULL)&&(current->vertexNum!=s))
			current=current->next;
		if(current->vertexNum!=s)
			current->next=source;
		else	// edge already exists
			free(source);		
	}
}

/** Function: bfsTraverse
 * -----------------------
 *  Performs a BFS traversal of a graph represented using adjacency list 
 *  starting from a given node upto another given node
 * 
 *  adj: Adjacency list of the graph
 *  numOfNodes: Number of nodes in the graph
 *  start: starting vertex
 *  end: ending vertex
 *  visited: Array depicting which vertices are visited
 *  
 *  returns: The level of end vertex from the start vertex if reachable,
 				-1 otherwise.
 */
int bfsTraverse(list *adj[], int numOfNodes, int start, int end) {
	// arrays of visited vertices and corresponding levels
	int visited[numOfNodes], levels[numOfNodes];	
	int i;
	for(i = 0; i < numOfNodes; i++) {
		visited[i] = 0;
		levels[i] = -1;
	}
	queue *q = createQueue(numOfNodes);  // Initializing the queue used in BFS
	enqueue(q, start);	// enqueue the starting vertex
	levels[start] = 0;	// make start node be at level 0
	
	do
	{
		int node=dequeue(q);	// get next node from front of queue
		visited[node] = 1;		// mark the node as visited
		
		if(node == end) {		// terminate traversal if end is reached
			freeQueue(q);		// free the queue after using
			return levels[end];
		}
		vertex *current = adj[node]->head;
		while(current != NULL) {
			// if a new vertex is reached then enqueue it
			if(!visited[current->vertexNum]) {
				enqueue(q, current->vertexNum);
				// set the level of newly visited node
				levels[current->vertexNum] = levels[node] + 1;	
			}
			current = current->next;
		}
	}
	while(!isEmpty(q));
	freeQueue(q);	// free the queue after using
	return -1;		// end vertex could not be reached
}

/** Function: readMaze
 * -----------------------
 *  Reads the maze as a character matrix from a given file
 * 
 *  maze: Character array to store the maze
 *  fileName: Name of the file containing the maze
 *
 *  returns: The number of valid moveable positions in the maze,
 				or -1 if the file could not be accessed
 */
int readMaze(char maze[DIM][DIM], char fileName[]) {
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL) {	// ensure fil is opened properly
		printf("File cannot be accessed!\n");
		return -1;
	}
	
	int i, nodes = 0;
	for(i = 0; i < DIM; i++) {
		int j;
		for(j = 0; j < DIM; j++) {
			char c;
			fscanf(fp, "%c", &c);
			if(c != '.' && c != '#') {	// handle \n and EOF
				if(!j) {
					i--;
					break;
				}
				j--;
			}
			if(c == '.')
				nodes++;
			maze[i][j] = c;		// put the character into the maze
		}
	}
	fclose(fp);
	
	return nodes;
}

/** Function: displayMaze
 * -----------------------
 *  Displays the maze as a character matrix on the screen
 *  Not explicitly required in the given problem.
 *
 *  maze: Character array storing the maze
 */
void displayMaze(char maze[DIM][DIM]) {
	int i;
	for(i = 0; i < DIM; i++) {
		int j;
		for(j = 0; j < DIM; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

/** Function: printList
 * -----------------------
 *  Displays the adjacency list of the generated graph.
 *  Not explicitly required in the given problem.
 *
 *  adjList: Adjacency list of the graph
 *  size: Number of nodes in the graph
 */
void printList(list *adjList[], int size)
{
	printf("The adjacency list is :");
	int i;
	for(i = 0; i < size; i++)
	{
		vertex *current=adjList[i]->head;
		printf("\nV%d ----> ",i);
		while(current)
		{
			printf("(V%d, %d, %d), \t",current->vertexNum, current->rowIdx, current->colIdx);
			current=current->next;
		}
	}
	printf("\n\n");
}

/** Function: max
 * -----------------------
 *  Gives the maximum of 2 values.
 *
 *  num1: The first value
 *  num2: The second value
 * 
 *  returns: The larger between num1 and num2
 */
int max(int num1, int num2) {
    return (num1 > num2 ) ? num1 : num2;
}

/** Function: generateGraph
 * -----------------------
 *  Generates the graph from the maze matrix as an adjacency list
 *  and finds the minimum number of moves required to finish the game.
 *  Displays -1 if maze does not lead to end point.
 *
 *  maze: The character matrix storing the maze
 *  nodes: Number of valid moveable positions in the maze
 */
void generateGraph(char maze[DIM][DIM], int nodes) {
	list *adjList[nodes];	// adjacency list declaration
	int i;
	for(i=0;i<nodes;i++) {	// adjacency list initialization
		adjList[i]=(list*)malloc(sizeof(list));
		adjList[i]->head=NULL;
	}
	int current = -1;	// holds the vertex number upto which is already discored
	int startNode, endNode;
	for(i = 0; i < DIM; i++) {
		int j;
		for(j = 0; j < DIM; j++) {
			if(maze[i][j] == '.') {
				
				// get vertex number for current node
				int s = mapNode(adjList, nodes, i, j, current);
				current = max(current, s);	
				// if node is in the first column then it must be the starting point
				if(!j)
					startNode = s;
				// if node is in the last column then it must be the ending point
				else if(j == (DIM-1)) 
					endNode = s;
				// find reachable node in next column
				if((j != DIM-1) && (maze[i][j+1] == '.')) {
					int d = mapNode(adjList, nodes, i, j+1, current);
					if(s==d)
						d++;
					current = max(current, d);
					addNewEdge(adjList, s, i, j, d, i, j+1);
				}
				// find reachable node in next row
				if((i != DIM-1) && (maze[i+1][j] == '.')) {
					int d = mapNode(adjList, nodes, i+1, j, current);
					if(s==d)
						d++;
					current = max(current, d);
					addNewEdge(adjList, s, i, j, d, i+1, j);
				}
			}
		}
	}
	// Find the minimum number of moves
	printf("%d\n", bfsTraverse(adjList, nodes, startNode, endNode)) ;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Please provide Maze input file name as argument!\n");
		return 1;
	}
	char maze[DIM][DIM];
	int nodes = readMaze(maze, argv[1]);
	//printf("Maze : \n");
	//displayMaze(maze);
	generateGraph(maze, nodes);
}

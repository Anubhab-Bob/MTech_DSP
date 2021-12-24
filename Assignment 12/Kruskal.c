/** This program maintains a disjoint set data structure to 
 * apply Kruskal's algorithm. The disjoint sets are maintained
 * using array for easy manipulation. 
 */
#include <stdio.h>
#include <stdlib.h>

/** Structure: edge
 * -----------------------------
 * Data structure to hold information of an edge of the graph
 */
struct edge {
	int source;
	int dest;
	int weight;
};

typedef struct edge edge;

/** Function: makeSet
 * -----------------------------
 * Creates a new disjoint set for a given value and saves its
 * corresponding representative as itself and also saves its rank.
 * 
 * representative: Holds the information of representative members 
 *                  of each disjoint set
 * rank: Holds the information of ranks of each disjoint set
 * x: The value to be part of the new set
 */
void makeSet(int representative[], int rank[], int x) {
    representative[x] = x;  // lone member is representative of its set
    rank[x] = 0;
}

/** Function: findSet
 * -----------------------------
 * Finds the representative element of the isjoint set 
 * whose part is the given value.
 * 
 * representative: Holds the information of representative members 
 *                  of each disjoint set
 * k: The value whose representative element is to be searched
 * 
 * returns: The representative value for k
 */
int findSet(int representative[], int k) {
    // if k is not the root, then k is not the representative of its group
    // then find representative of k using path compression
    if (representative[k] != k)
        representative[k] = findSet(representative, representative[k]);

    return representative[k];
}

/** Function: uniteSets
 * -----------------------------
 * Performs union of 2 disjoint sets with given representative 
 * elements by rank of the disjoint sets.
 * 
 * representative: Holds the information of representative members 
 *                  of each disjoint set
 * rank: Holds the information of ranks of each disjoint set
 * x: The representative value for the first disjoint set
 * y: The representative value for the second disjoint set
 */
void uniteSets(int representative[], int rank[], int x, int y) {
	// Perform union by rank
    if (rank[x] > rank[y])
        representative[y] = x;
    else if (rank[x] < rank[y])
        representative[x] = y;
    else {
        representative[x] = y;
        rank[y]++;
    }
}

/** Function: sortEdges
 * -----------------------------
 * Sorts the edges of a graph based on the edge weights using Bubble Sort.
 * 
 * edgeList: Array of all the edges of the graph
 * numEdges: The number of edges in the graph
 */
void sortEdges(edge edgeList[], int numEdges) {
	for(int i = 0; i < numEdges-1; i++) {
		for(int j = 0; j < numEdges-i-1; j++) {
			if(edgeList[j].weight > edgeList[j+1].weight) {     // swap
				edge e = edgeList[j];
				edgeList[j] = edgeList[j+1];
				edgeList[j+1] = e;
			}
		}
	}
}

/** Function: kruskalMST
 * -----------------------------
 * Applies Kruskal's algorithm to find the MST of a graph.
 * 
 * representative: Holds the information of representative members 
 *                  of each disjoint set
 * rank: Holds the information of ranks of each disjoint set
 * edgeList: Array of all the edges of the graph
 * numEdges: The number of edges in the graph
 */
void kruskalMST(int representative[], int rank[], edge edgeList[], int numEdges) {
	int spanningWeight = 0;
	printf("The MST contains the edges {");
	for(int i = 0; i < numEdges; i++) {
		int x = findSet(representative, edgeList[i].source);
		int y = findSet(representative, edgeList[i].dest);
		// uncomment to show the disjoint sets 		
		/*
		printf("\nEdge = (%d, %d)\n", edgeList[i].source+1, edgeList[i].dest+1);
		for(int j = 0; j < 5; j++) {
			printf("S = %d\t",j+1);
			for(int k = 0; k < 5; k++) {
				if(representative[k] == j)
					printf("%d, ", k+1);
			}
			printf("\b\b\n");
		}
		*/
		if(x != y) {
			uniteSets(representative, rank, x, y);
			spanningWeight += edgeList[i].weight;
			printf("(%d, %d), ", edgeList[i].source+1, edgeList[i].dest+1);
		}
	}
	printf("\b\b}\nTotal weight: %d\n", spanningWeight);
}

int main(int argc, char *argv[]) {
	// Take input from file
	if(argc != 2) {
		printf("Please give input file name as command line argument!\n");
		exit(0);
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL) {		// Terminate program if file could not be read
		printf("File could not be accessed!\n");
		exit(0);
	}
	
	int numNodes, numEdges;     
	// accept the number of nodes and edges in the graph respectively
	fscanf(fp, "%d %d", &numNodes, &numEdges);
	
	int representative[numNodes], rank[numNodes];
	edge edgeList[numEdges];
	
	for(int i = 0; i < numNodes; i++) {     // initialise the arrays
		representative[i] = -1;
		rank[i] = -1;
	}
	
	for(int i = 0; i < numNodes; i++)       // create disjoint sets for each node
		makeSet(representative, rank, i);
	int i = 0;
	while(!feof(fp)) {
		fscanf(fp, "%d %d %d", &edgeList[i].source, 
		                    &edgeList[i].dest, 
		                    &edgeList[i].weight);
		// validate terminal vertices
		if(edgeList[i].source <= 0 && edgeList[i].source > numNodes) {
		    printf("File contains wrong input!");
		    exit(0);
	    }
	    if(edgeList[i].dest <= 0 && edgeList[i].dest > numNodes) {
		    printf("File contains wrong input!");
		    exit(0);
	    }
		edgeList[i].source--;
		edgeList[i].dest--;
		i++;
	}
	if(i != numEdges) {     // validate input graph
		printf("File contains wrong input!\n");
		exit(0);
	}
	fclose(fp);     // close file after data is read
	
	// sort edges before applying Kruskal's algorithm
	sortEdges(edgeList, numEdges);
	
	kruskalMST(representative, rank, edgeList, numEdges);
}
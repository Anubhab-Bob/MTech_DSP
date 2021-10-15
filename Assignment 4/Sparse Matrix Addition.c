#include <stdio.h>
#include <stdlib.h>

/** Structure: element
 * --------------------
 *  A data structure to store the details of non-zero elements of a sparse matrix
 * 
 */
struct element {
    int row;
    int column;
    int value;
};
typedef struct element element;

/** Structure: node
 * --------------------
 *  A data structure to store the ADT of non-zero elements of a sparse matrix
 * 
 */
struct node {
    element e;
    struct node *next;
};
typedef struct node node;

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to a non-zero element in a sparse matrix
 * 
 * r: Row number of the non-zero element
 * c: Column number of the non-zero element
 * v: Non-zero element
 * 
 * returns: Address of the newly created node
 */
node* createNode(int r, int c, int v) {
    node *n = (node*)malloc(sizeof(node));
    n->e.row = r;
    n->e.column = c;
    n->e.value = v;
    n->next = NULL;
    return n;
}

/** Function: insertFront
 * ----------------------
 *  Inserts a new node at the front of a given linked list
 * 
 * head: Address of the pointer to the linked list
 * newNode: The new node to be inserted
 */
void insertFront(node **head, node **newNode) {
    if (*head == NULL)
        *head = *newNode;
    else {
        (*newNode)->next = *head;
        *head = *newNode;
    }
}

/** Function: showMatrix
 * ----------------------
 *  Displays a sparse matrix in traditional format
 * 
 * head: Address of the pointer to the linked list
 * m: The number of rows in the given matrix
 * n: The number of columns in the given matrix
 */
void showMatrix(int m, int n, node* head) {
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            node *tmp = head;
            int flag = 0;
            while(tmp) {
                if(tmp->e.row == i && tmp->e.column == j) {
                    printf("%d ", tmp->e.value);
                    flag = 1;
                }
                tmp = tmp->next;
            }
            if(!flag)   // no element present at the current index
                printf("0 ");
        }
        printf("\n");
    }
}

/** Function: addSparseMatrix
 * ----------------------
 *  Creates a node corresponding to a non-zero element in a sparse matrix
 * 
 * m: Number of rows of the matrix
 * n: Number of columns of the matrix
 * h1: Pointer to the 1st matrix
 * h2: Pointer to the 2nd matrix
 * 
 * returns: Address of the resulting matrix
 */
node* addSparseMatrix(int m, int n, node *h1, node *h2) {
    node *res = NULL;   // holds the resulting sparse matrix
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            node *t1 = h1, *t2 = h2;
            int value = 0;
            while(t1) {
                if(t1->e.row == i && t1->e.column == j) // get value of this index from 1st matrix
                    value = t1->e.value;
                t1 = t1->next;
            }
            while(t2) {
                if(t2->e.row == i && t2->e.column == j)// get value of this index from 2nd matrix
                    value += t2->e.value;
                t2 = t2->next;
            }
            if(value) {     // if value has been set, then new entry into result required
                node *tmp = createNode(i, j, value);
                insertFront(&res, &tmp);
            }
        }
    }
    return res;
}

/** Function: createSparseMatrix
 * ----------------------
 *  Creates a sparse matrix of given dimension using linked list 
 * 
 * m: The number of rows in the given matrix
 * n: The number of columns in the given matrix
 * nonZ: Number of non-zero elements in the matrix
 */
node* createSparseMatrix(int m, int n, int nonZ) {
    node *head = NULL;
    for (int i = 0; i < nonZ; i++) { 
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        if(r < 0 || c < 0 || r >= m || c >= n) {
            printf("INVALID INPUT");
            exit(0);
        }
        node *tmp = createNode(r, c, v);
        insertFront(&head, &tmp);
    }
    return head;
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
    int m, n, n1, n2;
    scanf("%d %d", &m, &n);     // get dimensions of matrices
    scanf("%d %d", &n1, &n2);   // get number of non-0 values
    if(m <= 0 || n <= 0 || n1 < 0 || n2 < 0 || n1 > (m * n) || n2 > (m *n)) {
        printf("INVALID INPUT");
        return 1;
    }
    // creating the matrices if input is valid
    node *head1 = createSparseMatrix(m, n, n1); 
    node *head2 = createSparseMatrix(m, n, n2);
    node *result = addSparseMatrix(m, n, head1, head2);
    showMatrix(m, n, result);   // display result in traditional format
    // free the linked lists
    freeList(head1);
    freeList(head2);
    freeList(result);
}
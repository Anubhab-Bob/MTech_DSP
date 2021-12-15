#include <stdio.h>
#include <stdlib.h>

/** Structure: node
 * --------------------
 *  A data structure to store each node of the BST 
 */
struct node {
    int key;
    struct node *left;
    struct node *right;
};
typedef struct node node;

/** Structure: tree
 * --------------------
 *  A data structure to store a BST 
 */
struct tree {
    node *root;
    int count;
};
typedef struct tree bst;

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to given integer value
 * 
 * data: Element to be inserted in the BST
 * 
 * returns: Address of the newly created node
 */
node* createNode(int data) {
	node *tmp = (node*)malloc(sizeof(node));
    tmp->key = data; 
    tmp->left = NULL;
    tmp->right = NULL;
    
    return tmp;
}

/** Function: createTree
 * ----------------------
 *  Creates a blank BST
 * 
 * returns: Address of the newly created BST
 */
bst *createTree() {
    bst *t = (bst*)malloc(sizeof(bst));
    t->root = NULL;
    t->count = 0;   // number of nodes in the tree
    return t;
}

/** Function: LookUp
 * ----------------------
 *  Searches a given BST for a given key
 * 
 * t: The BST to search in
 * searchKey: Element to be searched in the BST
 * 
 * returns: 1 if searchKey is present in t, 0 otherwise
 */
int LookUp(bst *t, int searchKey) {
    node *tmp = t->root;
    while(tmp != NULL) {
        if(tmp->key == searchKey)   // key found
            return 1;
        if(tmp->key < searchKey)
            tmp = tmp->right;
        else if(tmp->key > searchKey)
            tmp = tmp->left;
    }
    return 0;   // key not found
}

/** Function: Insert
 * ----------------------
 *  Inserts a given value in a given BST
 * 
 * t: The BST in which to insert
 * newKey: Integer to be inserted in the BST
 */
 void Insert(bst *t, int newKey) {
    if(t->root == NULL) {  // BST is empty
        node *newNode = createNode(newKey);
        t->root = newNode;
        return;
    }
    node *tmp = t->root;
    node *newNode = createNode(newKey);
    while(tmp != NULL) {
        if(tmp->key == newKey) {  // key already exists in BST
        printf("%d exists\n", newKey);
        	free(newNode);
		    return;
        }
        if(tmp->key < newKey) {
            if(tmp->right == NULL) {
            	tmp->right = newNode;
            	break;
            }
			tmp = tmp->right;            
        }
        if(tmp->key > newKey){
        	if(tmp->left == NULL) {
            	tmp->left = newNode;
            	break;
            }
			tmp = tmp->left;
		}
    }
    t->count++; // increment number of nodes in the BST
}

/** Function: inorderSuccessor
 * ----------------------
 *  Finds the inorder successor of a node
 * 
 * head: Address of the node whose successor is to be found
 * p: The inorder successor, initially empty
 * 
 * returns: The address of the inorder successor in p
 */
node* inorderSuccessor(node **head, node *p)
{
	//The right subtree contains the inorder successor
	p=(*head)->right;
	// leftmost child of right subtree is inorder successor
	while(p->left != NULL)  
		p=p->left;
	
	return p;
}

/** Function: deleteNode
 * ----------------------
 *  Deletes a given value from a subtree recursively
 * 
 * root: The address of the root of the subtree in which to delete
 * key: Integer to be deleted from the subtree
 * 
 * returns: The address of the root of the subtree after deletion
 */
node* deleteNode(node *root, int key) {
    if(root->key < key)
        root->right = deleteNode(root->right, key);
    else if(root->key > key)
        root->left = deleteNode(root->left, key);
    else if(root->key == key) {
        //Node with only one child or no child
	    if (root->left == NULL)	{
            node *temp = root->right;
            free(root);
    	    return temp;
        }
	    else if (root->right == NULL) {
        	node *temp = root->left;
        	free(root);
	        return temp;
    	}
        //Node with two children: replace node with inorder successor
    	node *temp = inorderSuccessor(&root, temp);
        //Copy the inorder successor's content to this node
	    root->key = temp->key;
	    //Delete the inorder successor
    	root->right = deleteNode(root->right, temp->key);
    }
    
    return root;
}

/** Function: Delete
 * ----------------------
 *  Deletes a given value from a given BST
 * 
 * t: The BST from which to delete
 * deletionKey: Integer to be deleted from the BST
 */
void Delete(bst *t, int deletionKey) {
    if(!LookUp(t, deletionKey))   // element does not exit in BST
        return;
    t->root = deleteNode(t->root, deletionKey);
    t->count--;
}

/** Function: max
 * ----------------------
 *  Gives the maximum value between 2 integers
 * 
 * a: The first integer to compare
 * b: The first second integer to compare
 * 
 * returns: Maximum of a and b
 */
int max(int a, int b) {
    if(a < b)   
        return b;
    return a;
}

/** Function: heightFromNode
 * ----------------------
 *  Gives the height of a subtree from a given node
 * 
 * node: The root of the subtree whose height is to be determined
 * 
 * returns: The height of the subtree
 */
int heightFromNode(node *node) {
    if(node == NULL)
        return 0;
    
    return(max(heightFromNode(node->left), heightFromNode(node->right)) + 1);
}

/** Function: GetHeight
 * ----------------------
 *  Gives the height of a given BST
 * 
 * t: The BST to check
 * 
 * returns: height of t
 */
int GetHeight(bst *t) {
    return heightFromNode(t->root) - 1;
}

/** Function: inorder
 * ----------------------
 *  Gives the inorder traversal of subtree of a BST from a given root
 * 
 * root: The root of the subtree whose inprder traversal is needed
 */
void inorder(node *root) {
    if(root->left != NULL)
        inorder(root->left);
    printf("%d ", root->key);
    if(root->right != NULL)
        inorder(root->right);
}

/** Function: PrintSorted
 * ----------------------
 *  Displays the elements of a given BST in non-decreasing order
 * 
 * t: The BST to traverse
 */
 void PrintSorted(bst *t) {
    if(t->root == NULL) {
        printf("BST empty!");
        return;
    }
    inorder(t->root);
}

/** Function: freeBST
 * ----------------------
 *  Frees the memory associated with a given BST
 * 
 * t: The BST to free
 */
void freeBST(bst *t) {
    while(t->count)
        Delete(t, t->root->key);
}

int main() {
    bst *t = createTree();  // creating blank tree
    int cont = 1;   // choice of continuation
    while(cont) {
        int choice, value;
        scanf("%d", &choice);
        switch(choice) {
            case 1  :   scanf("%d", &value);
                        Insert(t, value);
                        break;
            case 2  :   scanf("%d", &value);
                        Delete(t, value);
                        break;
            case 3  :   scanf("%d", &value);
                        printf("%d ", LookUp(t, value));
                        break;
            case 4  :   printf("%d ", GetHeight(t));
                        break;
            case 5  :   PrintSorted(t);
                        break;
            case -1 :   freeBST(t); // free all memory associated with the tree
                        cont = 0;
                        break;
        }
    }
}
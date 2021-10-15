#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

/** Structure: node
 * --------------------
 *  A data structure to store the ADT for operators
 * 
 */
struct node {
    char op;
    struct node *next;
};
typedef struct node node;

/** Function: createNode
 * ----------------------
 *  Creates a node corresponding to an operator in the expression
 * 
 * c: The operator to be pushed
 * 
 * returns: Address of the newly created node
 */
node* createNode(char c) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->op = c;
    newNode->next = NULL;
    
    return newNode;
}

/* Function: stringLength
 * ----------------------
 *  Gives the length of a given string
 *
 *  c: Address of the string whose length is to be computed
 
 *  returns: The length of c
 */
int stringLength (char *c) {
    int i = 0;
    for (; c[i] != '\0'; i++);
    
    return i;
}

/* Function: isEmpty
 * ----------------------
 *  Checks if a given stack is empty
 *
 *  st: Address of the head node holding the top of stack
 *
 *  returns: 1 if st is empty, 0 otherwise
 */
int isEmpty(node *st)
{
    if (st == NULL)    // Stack Underflow!
        return 1;
    return 0;
}

/** Function: push
 * ----------------------
 *  Inserts a new node of given value at the front of a given linked list
 * 
 * head: Address of the pointer to the top of linked list stack
 * c: The new character to be inserted
 */
void push(node **head, char c) {
    node *newNode = createNode(c);  // creating a new node corresponding to the operator
    if (*head == NULL)
        *head = newNode;
    else {
        newNode->next = *head;
        *head = newNode;    // new node coming at top of stack
    }
}

/** Function: pop
 * ----------------------
 *  Pops the front element of a given linked list
 * 
 * head: Address of the pointer to the top of linked list stack
 * 
 * returns: The character popped from top of stack as a string
 */
char pop(node **head)
{
	node *tmp=*head;
	*head=tmp->next;
	char popped = tmp->op;
	free(tmp);  // pop frees the memory allocated to the deleted node
	
	return popped;
}

/* Function: isOperand
 * ----------------------
 *  Checks if a given character is a valid operand
 *
 *  c: The character to be checked
 *
 *  returns: 1 if c is operand, 0 otherwise
 */
int isOperand(char c)
{
	if((c>='0' && c<='9')||(c>='a' && c<='z')||(c>='A' && c<='Z'))
		return 1;
	return 0;
}

/* Function: addToPostfix
 * ----------------------
 *  Appends a string to the end of the postfix string
 *
 *  post: Address of the postfix string
 *  op: Address of the string to append
 */
void addToPostfix(char *post, char *op) {
    int p = stringLength(post);
    int i, flag = 0;
    // append characters from other string to end of postfix string
    for(i = 0; i < stringLength(op); i++) { 
            post[p++] = op[i];
    }
    post[p++] = ' ';
    post[p] = '\0';
}

/** Function: getTop
 * ------------------
 * Gives the element at the top of stack without popping
 * 
 * st: Address of the pointer to the top of linked list stack
 * 
 * returns: The character at top of stack
 */ 
char getTop(node *st) {
    return st->op;
}

int main() {
    char input[MAX]="", postfix[MAX]="";
    node *stack = NULL;
    fgets(input, MAX, stdin);   // maximum size of input string is considered MAX
    input[stringLength(input) - 1] = '\0'; // replace '\n' with '\0'
    char *token = strtok(input, " \n");   // separate the tokens from the input
    while(token != NULL) {
    	if(*token == '(')
    		push(&stack, *token);
    	else if(*token == '*' || *token == '/' || *token == '%') {
			if(stack != NULL) {
			    // pop operators of similar or greater priority
				if(getTop(stack) == '*' || getTop(stack) == '/' || getTop(stack) == '%') {
					char c[2] = "\0";
					c[0] = pop(&stack); // popped charater converted to string
					addToPostfix(postfix, c);
				}
			}
			push(&stack, *token);   // push the current operator into stack
		}
		else if(*token == '+' || *token == '-') {
			if(stack != NULL) {
			    // pop operators of similar or greater priority
				while(getTop(stack) != '(') { 
					char c[2] = "\0";
					c[0] = pop(&stack);  // popped charater converted to string
					addToPostfix(postfix, c);
					if(stack == NULL)
						break;
				}
			}
			push(&stack, *token);   // push the current operator into stack
		}
		else if(*token == ')') {
			while(getTop(stack) != '('){
				char c[2] = "\0";
				c[0] = pop(&stack);  // popped charater converted to string
				addToPostfix(postfix, c);
			}
			pop(&stack);    // pop the '(' without appending to postfix string
		}
        else if(isOperand(*token))  // operands directly get into postfix string
            addToPostfix(postfix, token);
        token = strtok(NULL, " \n");
	}
	while (stack != NULL) { // append the remaining operators 
		char c[2] = "\0";
		c[0] = pop(&stack);  // popped charater converted to string
		if(c[0] != '(') // pop the '(' without appending to postfix string
			addToPostfix(postfix, c);
	}
	printf("%s", postfix);  // display the final postfix string
}
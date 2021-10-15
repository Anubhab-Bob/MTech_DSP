#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/** Structure: stack
 * ------------------
 *  A stack data structure with dynamic capacity
 */
struct stack
{
    int top;
    int size;
    int *data;
};
typedef struct stack stack;

// prototypes of functions used in the program
stack* createStack(int size);
int isEmpty(stack *st);
int isFull(stack *st);
void push(stack *st, int value);
int pop(stack *st);
int getTop(stack *st);
stack* resizeStack(stack *st);
void freeStack(stack *st);

/** Function: createStack
 * -----------------------
 *  Creates a stack of dynamic capacity using struct stack 
 *  
 *  size: size of the stack to create
 *  returns: Address of the created stack
 */
stack* createStack(int size) {
    stack *st = (stack*)malloc(sizeof(stack));
    st->top = -1;
    st->size = size;
    st->data = (int*)malloc(sizeof(int) * st->size);
    return st;
}

/** Function: isEmpty
 * -------------------
 *  Checks if a given stack is empty
 * 
 *  st: The stack to check
 *  returns: 1 if st is empty, 0 otherwise
 */
int isEmpty(stack *st) {
    if(st->top < 0)
        return 1;
    return 0;
}

/** Function: isFull
 * -------------------
 *  Checks if a given stack is full
 * 
 *  st: The stack to check
 *  returns: 1 if st is full, 0 otherwise
 */
int isFull(stack *st) {
    if(st->top == (st->size - 1))
        return 1;
    return 0;
}

/** Function: push
 * -------------------
 *  Inserts a given value into a given stack
 * 
 *  st: The stack in which to insert
 *  value: The value to insert into st
 */
void push(stack *st, int value) {
    st->data[++st->top] = value;
}

/** Function: pop
 * -------------------
 *  Removes the top element from a given stack
 * 
 *  st: The stack from which to pop
 *  returns: The value popped from st
 */
int pop(stack *st) {
    return st->data[st->top--];
}

/** Function: getTop
 * -------------------
 *  Gives the top element from a given stack
 * 
 *  st: The stack from which to get
 *  returns: The value at the top of st
 */
int getTop(stack *st) {
    return st->data[st->top];
}

/** Function: resizeStack
 * -------------------
 *  Doubles the capacity of a given stack
 * 
 *  st: The stack to be doubled
 *  returns: Address of the stack with double capacity
 */
stack* resizeStack(stack *st) {
    stack *newS = createStack(st->size * 2);
    int i;
    for(i = 0; i <= st->top; i++)
        push(newS, st->data[i]);
        
    free(st);       // free old stack
    
    return newS;
}

/** Function: freeStack
 * -------------------
 *  Frees all the memory associated with a given stack
 * 
 *  st: The stack to be deallocated
 */
void freeStack(stack *st) {
    free(st->data);
    free(st);
}

int main() {
    int initialSize = 4;                    // initial size of stack is 4
    stack *s = createStack(initialSize);
    char input[MAX];            // maximum size of input is considered to be 100
    fgets(input, MAX, stdin);
    char *token = strtok(input, " \n");   // separate the tokens from the input
    while(token != NULL) {
        int op1, op2, res;          // variables to hold operands and results
        switch(*token) {
            case '+':               // Addition
                if(isEmpty(s)) {
                    return 1;
                }
                op2 = pop(s);
                if(isEmpty(s)) {
                    return 1;
                }
                op1 = pop(s);
                res = op1 + op2;
                if(isFull(s))
                    s = resizeStack(s);
                push(s, res);
                break;
            case '-':               // Subtraction
                if(isEmpty(s)) {
                    return 1;
                }
                op2 = pop(s);
                if(isEmpty(s)) {
                    return 1;
                }
                op1 = pop(s);
                res = op1 - op2;
                if(isFull(s))
                    s = resizeStack(s);
                push(s, res);
                break;
            case '*':               // Multiplication
                if(isEmpty(s)) {
                    return 1;
                }
                op2 = pop(s);
                if(isEmpty(s)) {
                    return 1;
                }
                op1 = pop(s);
                res = op1 * op2;
                if(isFull(s))
                    s = resizeStack(s);
                push(s, res);
                break;
            case '/':               // Division
                if(isEmpty(s)) {
                    return 1;
                }
                op2 = pop(s);
                if(!op2) {
                    printf("DIVBYZERO");
                    exit(0);
                }
                if(isEmpty(s)) {
                    return 1;
                }
                op1 = pop(s);
                res = (int) (op1 / op2);
                if(isFull(s))
                    s = resizeStack(s);
                push(s, res);
                break;
            default:                // Operand or end of input
                if(*token >= '0' && *token <= '9') {
                    if(isFull(s))
                        s = resizeStack(s);
                    push(s, atoi(token));
                }
                break;
        }
        token = strtok(NULL, " \n");
    }
    printf("%d", pop(s));       // Pop the final result
    freeStack(s);       // deallocate stack once complete
    
    return 0;
}


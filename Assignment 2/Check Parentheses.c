#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

/* Structure: stack
 * -----------------
 *  A stack data structure with MAXSIZE capacity  
 */
typedef struct stack
{
    int data[MAXSIZE];
    int top;
} 
stack;

/* Function: createStack
 * ----------------------
 *  Creates a stack using using struct stack 
 *
 *  returns: Address of the stack in memory
 */
stack* createStack()
{
    stack* st = (stack*)malloc(sizeof(stack));
    for (int i = 0; i < MAXSIZE; i++)   // initialize data in stack
        st->data[i] = '\0';
    st->top = -1;   // initialize stack top
    
    return st;
}

/* Function: push
 * ----------------------
 *  Pushes a passed value in a given stack 
 *
 *  st: Address of the stack in which value is to be pushed
 *  value: Value to be pushed into the given stack
 *
 *  returns: 1 if push is succesful, 0 otherwise
 */
int push(stack* st, int value)
{
    if (st->top >= (MAXSIZE - 1))   // Stack Overflow!
        return 0;
        
    st->data[++st->top] = value;
    
    return 1;
}

/* Function: pop
 * ----------------------
 *  Pops the top element from a given stack 
 *
 *  st: Address of the stack from which to be popped
 *
 *  returns: The popped element if possible, 0 otherwise
 */
int pop(stack* st)
{
    if (st->top < 0)    // Stack Underflow!
        return 0;
    
    return (st->data[st->top--]);
}

/* Function: checkParentheses
 * ----------------------
 *  Checks if the parentheses are balanced 
 *
 *  st: Address of the stack in which value is to be pushed
 *  input: Argument string to be parsed
 *
 *  returns: 1 if parantheses are balanced, 0 otherwise
 */
int checkParentheses(char *input, stack* st)
{
    int result = 1; // flag variable to hold result of interim push, pop
    // Go through input until input expires or push or pop fails
    for (int i = 0; input[i] != '\0' && result; i++)
    {
        if (input[i] == '{')
            result = push(st, input[i]);
        if (input[i] == '}')
            result = pop(st);
    }
    
    // balanced if all pushes and pops are successful and stack is empty
    if (result && st->top == -1)     
        return 1;
    return 0;
}

int main()
{
    stack* s = createStack();
    char input[MAXSIZE] = "";
    fgets(input, MAXSIZE, stdin);
    printf("%d", checkParentheses(input, s));
}

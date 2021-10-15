#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

/* Structure: stack
 * -----------------
 *  A stack data structure with MAXSIZE capacity
 */
struct stack
{
    char data[MAXSIZE];
    int top;
};
typedef struct stack stack;

/* Structure: queue
 * -----------------
 *  A queue data structure with MAXSIZE capacity
 */
struct queue
{
    char data[MAXSIZE];
    int front;
    int rear;
};
typedef struct queue queue;

/* Function: createStack
 *-----------------------
 *  Creates a stack using struct stack 
 *
 *  returns: Address of the stack in memory
 */
stack* createStack()
{
    stack* st = (stack*)malloc(sizeof(stack));
    for (int i = 0; i < MAXSIZE; i++)
        st->data[i] = '\0';
    st->top = -1;
    
    return st;
}

/* Function: createQueue
 *-----------------------
 *  Creates a queue using struct queue 
 *
 *  returns: Address of the queue in memory
 */
queue* createQueue()
{
    queue* qu = (queue*)malloc(sizeof(queue));
    for (int i = 0; i < MAXSIZE; i++)
        qu->data[i] = '\0';
    qu->front = -1;
    qu->rear = -1;
    
    return qu;
}

/* Function: isEmptyStack
 * ----------------------
 *  Checks if a given stack is empty
 *
 *  st: Address of the stack to check
 *  returns: 1 if st is empty, 0 otherwise
 */
int isEmptyStack(stack *st)
{
    if (st->top < 0)    // Stack Underflow!
        return 1;
    return 0;
}

/* Function: isEmptyQueue
 * ----------------------
 *  Checks if a given queue is empty
 *
 *  qu: Address of the queue to check
 *  returns: 1 if qu is empty, 0 otherwise
 */
int isEmptyQueue(queue *qu)
{
    if (qu->front < 0)    // Stack Underflow!
        return 1;
    return 0;
}

/* Function: isFullStack
 * ----------------------
 *  Checks if a given stack is full
 *
 *  st: Address of the stack to check
 *  returns: 1 if st is full, 0 otherwise
 */
int isFullStack(stack *st)
{
    if (st->top >= (MAXSIZE - 1))   // Stack Overflow!
        return 1;
    return 0;
}

/* Function: isFullQueue
 * ----------------------
 *  Checks if a given queue is full
 *
 *  qu: Address of the queue to check
 *  returns: 1 if qu is full, 0 otherwise
 */
int isFullQueue(queue *qu)
{
    if(qu->rear >= (MAXSIZE - 1))   // Queue Overflow!
        return 1;
    return 0;
}

/* Function: push
 *-----------------------
 *  Pushes a passed value in a given stack
 *
 *  st: Address of the stack in which the value is to be pushed
 *  value: Value to be pushed into the given stack
 *
 *  returns: 1 if push is successful, 0 otherwise
 */
int push(stack *st, char value)
{
    if (isFullStack(st))   // Stack overflow!
        return 0;
    
    st->data[++st->top] = value;
    
    return 1;
}

/* Function: pop
 *-----------------------
 *  Pops the top element from a given stack
 *
 *  st: Address of the stack from which the value is to be popped
 *  
 *  returns: The popped element if possible, '\0' otherwise
 */
char pop(stack* st)
{
    if (isEmptyStack(st))    // Stack Underflow!
        return '\0';
        
    return (st->data[st->top--]);
}

/* Function: enqueue
 *-----------------------
 *  Inserts a passed value in a given queue
 *
 *  qu: Address of the queue in which the value is to be pushed
 *  value: Value to be pushed into the given queue
 *
 *  returns: 1 if insertion is successful, 0 otherwise
 */
int enqueue(queue* qu, char value)
{
    if(isFullQueue(qu))   // Queue Overflow!
        return 0;
    
    qu->data[++qu->rear] = value;
    if(qu->front < 0)
        qu->front = 0;
        
    return 1;
}

/* Function: dequeue
 *-----------------------
 *  Removes the front element from a given queue
 *
 *  qu: Address of the queue from which the value is to be removed
 *  
 *  returns: The removed element if possible, '\0' otherwise
 */
char dequeue(queue* qu)
{
    if (isEmptyQueue(qu))  // Queue Underflow
        return '\0';
    
    char removed = qu->data[qu->front++];
    
    if(qu->front > qu->rear)    // Reset front and rear if queue is empty
    {
        qu->front = -1;
        qu->rear = -1;
    }
    
    return removed;
}

/* Function: checkPalindrome
 *-----------------------
 *  Checks if a given string is palindrome or not using stack and queue
 *
 *  input: Argument string to be parsed
 *  st: Address of the stack to be used
 *  qu: Address of the queue to be used
 *  
 *  returns: 1 if input is palindrome, 0 otherwise
 */
int checkPalindrome(char* input, stack* st, queue* qu)
{
    for(int i = 0; (input[i] != '\n') && (input[i] != '\0'); i++)   // fgets includes '\n' in input
    {
        push(st, input[i]);
        enqueue(qu, input[i]);
    }
    while(!isEmptyQueue(qu) || !isEmptyStack(st))   // continue till stack or queue is not empty
    {
        char popped = pop(st); 
        char dequeued = dequeue(qu);
        // input is not palindrome if there is underflow or popped and dequeued mismatch
        if(popped == '\0' || dequeued == '\0' || popped != dequeued)
            return 0;
    }
    
    return 1;
}

int main()
{
    queue* q = createQueue();
    stack* s = createStack();
    char input[MAXSIZE] = "";
    fgets(input, MAXSIZE, stdin);
    printf("%d", checkPalindrome(input, s, q));
    free(q);
    free(s);
}

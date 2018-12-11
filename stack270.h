/*  cs270_hw7
    Eddie Chan
    stack270.h
    Header file for stack functions */

struct stack270 {
    int topIndex;
    int *contents;
    int max;
};

// Function Prototypes
// returns  a newly initialized (empty) stack with enough space of size integers, or NULL if an error occurs
struct stack270 initStack(int size);  

// push value onto stk; returns 0 if successful, -1 if an error occurs
int push(struct stack270 *stk, int value); 

 // removes the value on top  of stack stk; returns 0 if successful, -1 if an error occurs
int pop(struct stack270 *stk);

// address given by value contains a copy of the item at top of stack; returns 0 if successful, -1 if an error occurs
int peek(struct stack270 *stk, int *value); 

// pushes a duplicate of the top value onto the stack; returns the usual
int dup(struct stack270 *stk); 

// removes the top two items on the stack, adds them, and pushes the result; returns the usual
int add(struct stack270 *stk); 
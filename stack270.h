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

// Free malloc'd space
void freeStack(struct stack270 *stk);

char **readBytecode(char *filename);

int iadd(struct stack270 *stk);

int iand(struct stack270 *stk);

int isub(struct stack270 *stk);

int imul(struct stack270 *stk);

int idiv(struct stack270 *stk);

int ineg(struct stack270 *stk);

int ior(struct stack270 *stk);

int ishl(struct stack270 *stk);

int ishr(struct stack270 *stk);

int iconst_0(struct stack270 *stk);

int iconst_1(struct stack270 *stk);

int iconst_2(struct stack270 *stk);

int iconst(struct stack270 *stk, int operand);

int ifeq(struct stack270 *stk);

int ifne(struct stack270 *stk);

int iinc(struct stack270 *stk);

int idec(struct stack270 *stk);

int igoto(struct stack270 *stk, int operand);

int ireturn(struct stack270 *stk);


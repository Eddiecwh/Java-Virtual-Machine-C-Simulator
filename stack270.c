/*  cs270_hw7
    Eddie Chan
    stack270.c
    This program is designed to simulate the behavior of executing
    (a small subset) of Java bytecode operations - like the Java Virtual Machine.
    This library holds those functions */

#include "stack270.h"
#include <stdio.h>
#include <malloc/_malloc.h>
#include <stdlib.h>
#include <string.h>

int firstItem;
int secondItem;
int result;

struct stack270 initStack(int size)
{
    struct stack270 *stk = (struct stack270 *)malloc(sizeof(struct stack270));
    stk->topIndex = -1;
    // Don't return NULL just keep contents as NULL
    stk->contents = (int *)malloc(sizeof(int) * size);
    stk->max = size;
    return *stk;
}

int push(struct stack270 *stk, int value)
{
    int item;
    // If stack's tops equal to last index then stack is full
    if (stk->topIndex == stk->max - 1)
    {
        printf("Stack is full\n");
        return -1;
    }
    else
    {
        stk->contents[++stk->topIndex] = value;
        return 0;
    }
}

int pop(struct stack270 *stk)
{
    int item;
    if (stk->topIndex == -1)
    {
        printf("Stack is empty\n\n");
        return -1;
    }
    else
    {
        item = stk->contents[stk->topIndex--];
        printf("%d has been popped\n", item);
        return 0;
    }
}

int peek(struct stack270 *stk, int *value)
{
    int topItem;
    if (stk->topIndex == -1)
    {
        printf("Stack is empty\n\n");
        return -1;
    }
    else
    {
        *value = stk->contents[stk->topIndex];
        topItem = *value;
        printf("The item on the top of the stack is: %d\n\n", topItem);
        return 0;
    }
}

int dup(struct stack270 *stk)
{
    int dupItem;
    if (stk->topIndex == -1)
    {
        printf("Stack is empty\n\n");
        return -1;
    }
    else
    {
        dupItem = stk->contents[stk->topIndex];
        stk->contents[++stk->topIndex] = dupItem;
        printf("Your duplicate item: %d has been pushed onto the stack\n\n", dupItem);
        return 0;
    }
}

// readBytecode: given filename, opens the file, reads each line into an array of C-strings, and closes the file
// Returns: array of C-strings
// Limitation: works on files with 256 lines or less
char **readBytecode(char *filename)
{
    static char *codes[256];
    int i, MAXS = 256;
    char *blankp, instr[MAXS];
    FILE *stream;

    stream = fopen(filename, "r");
    if (stream == NULL)
        return NULL;

    i = 0;
    while (fgets(instr, MAXS, stream) != NULL)
    {
        int len = strlen(instr);
        codes[i] = (char *)malloc(len);
        if (codes[i] == NULL)
            return NULL;
        strncpy(codes[i], instr, len - 1);
        codes[i][len] = '\0';
        if ((blankp = strchr(codes[i], ' ')) != NULL)
        {
            *blankp = '\0';
            codes[++i] = blankp + 1;
        }
        i++;
    }

    return codes;
}

/* remove top two values from the stack, add them, push the result back onto 
   stack */
int iadd(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // subtract the first value from the second value
    result = secondItem + firstItem;

    // Push shifted value back onto the stack
    push(stk, result);

    return 0;
}

/* Remove top two values from the stack, compute logcal and of the first value
   and the second, push the result back onto the stack */
int iand(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Compute logical and
    result = firstItem & secondItem;
    push(stk, result);

    return 0;
}

/* remove top two values from the stack, subtract the first value removed from 
   the second, push the result back onto stack */
int isub(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // subtract the first value from the second value
    result = secondItem - firstItem;

    // Push shifted value back onto the stack
    push(stk, result);

    return 0;
}

/* remove top two values from the stack, multiply them, push the (integer) 
   result back onto stack */
int imul(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Multiply the top two elements
    result = firstItem * secondItem;
    push(stk, result);

    return result;
}

/* Remove top two values from the stack, divide them, push the (integer) result
   back onto stack */
int idiv(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Divide the top two elements
    result = firstItem / secondItem;
    push(stk, result);

    return result;
}

/* Remove top two values from the stack, divide them, push the (integer) result
   back onto stack */
int ineg(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    // Negate the top value from the stack
    result = !firstItem;

    push(stk, result);

    return result;
}

/* remove top two values from the stack, compute logical or, push the result back 
   onto stack */
int ior(struct stack270 *stk){
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Divide the top two elements
    result = firstItem || secondItem;
    push(stk, result);

    return result;
}

/* remove top two values from the stack, shift the second value removed left a
   number of bits given by the first value removed, push the result back onto stack */
int ishl(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Shift second value by first value
    result = secondItem << firstItem;

    // Push shifted value back onto the stack
    push(stk, result);

    return 0;
}

/* remove top two values from the stack, shift the second value removed right 
   a number of bits given by the first value removed, push the result back onto 
   stack */
int ishr(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);
    // Store next into secondItem
    secondItem = stk->contents[stk->topIndex];
    pop(stk);

    // Shift second value by first value
    result = secondItem >> firstItem;

    // Push shifted value back onto the stack
    push(stk, result);

    return 0;
}

int iconst_0(struct stack270 *stk)
{
    push(stk, 0);
    return 0;
}

int iconst_1(struct stack270 *stk)
{
    push(stk, 1);
    return 0;
}

int iconst_2(struct stack270 *stk)
{
    push(stk, 2);
    return 0;
}

/* Push the value x onto the stack */
int iconst(struct stack270 *stk, int operand)
{
    push(stk, operand);
    return 0; // Successfully pushed
}

/* remove value from the top of stack; if this value is zero, skip forward x 
   instructions (or backward if x is negative) */
int ifeq(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    // If value at the top of the stack is 0
    if (firstItem == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/* remove value from the top of stack; if this value is not zero, skip forward x 
   instructions (or backward if x is negative) */
int ifne(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    // If value at the top of the stack is not 0
    if (firstItem != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* increment the value on top of stack by one (which means: remove value from 
   top of stack, add one to it, push result back) */
int iinc(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    // Increment value at the top of the stack by 1
    result = firstItem++;
    push(stk, result);

    return result;
}

/* decrement the value on top of stack by one */
int idec(struct stack270 *stk)
{
    // Store top item into firstItem
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    // Decrement value at the top of the stack by 1
    result = firstItem--;
    push(stk, result);

    return result;
}


/* skip forward x instructions (or backward if x is negative) */
int igoto(struct stack270 *stk, int operand)
{
    if (operand > 0)
    {
        return 1;
    }
    if (operand < 0)
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

/* remove the value from top of stack and print it out as the result */
int ireturn(struct stack270 *stk)
{
    firstItem = stk->contents[stk->topIndex];
    pop(stk);

    return firstItem;
}

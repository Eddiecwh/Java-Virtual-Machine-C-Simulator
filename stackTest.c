/* Eddie Chan
   stackTest.c
   CSCI_270
   This program is designed to test functions from stack270.c */

#include "stack270.c"

int main()
{
    int size = 50;
    int choice;
    int num;
    int value;

    printf("Hello and welcome to the stack program!\n");
    struct stack270 stack = initStack(size);

    /* Uncomment the line below for extra credit test file */
    char *p = "maxfile.class";
    // char *p = "testfile.class";
    char **lines = readBytecode(p);

    int operand;
    int returnCode;
    int returnValue;

    for (int i = 0; lines[i] != NULL; i++)
    {
        printf("Instruction line: %s\n", lines[i]);
        if (strncmp(lines[i], "iconst_0", 8) == 0) 
        {
            iconst_0(&stack);
            printf("0 has been pushed onto the stack\n\n");
        }
        else if (strncmp(lines[i], "iconst_1", 8) == 0) 
        {
            iconst_1(&stack);
            printf("1 has been pushed onto the stack\n\n");
        }
        else if (strncmp(lines[i], "iconst_2", 8) == 0) 
        {
            iconst_2(&stack);
            printf("2 has been pushed onto the stack\n\n");
        }
        else if (strncmp(lines[i], "iconst", 6) == 0)
        {
            operand = atoi(lines[i+1]);
            iconst(&stack, operand);
            printf("%d, has been pushed onto the stack\n\n", operand);
        } 
        else if (strncmp(lines[i], "iand", 4) == 0)
        {
            iand(&stack);
            printf("The top values have been &'d and pushed to the top of the stack\n\n");
        }
        else if (strncmp(lines[i], "ishr", 4) == 0) 
        {
            ishr(&stack);
        }
        else if (strncmp(lines[i], "ishl", 4) == 0) 
        {
            ishl(&stack);
        }
        else if (strncmp(lines[i], "dup", 3) == 0) 
        {
            dup(&stack);
        } 
        else if (strncmp(lines[i], "isub", 4) == 0)
        {
            isub(&stack);
        }
        else if (strncmp(lines[i], "ifne", 4) == 0) 
        {
            operand = atoi(lines[i+1]);
            printf("ifne's operand: %d\n", operand);
            returnCode = ifne(&stack);
            // If top of stack is not 0 and x is positive
            if (returnCode == 1 && operand > 0) {
                i+=operand; // Skip forward 'x' steps
            } else if (returnCode == 1 && operand < 0) {
                i-=operand; // Go backwards 'x' steps
            } else if (returnCode == 0){
                // Do nothing, skip to next instruction
            }
        }
        else if (strncmp(lines[i], "ifeq", 4) == 0)
        {
            operand = atoi(lines[i+1]);
            printf("ifeq's operand: %d\n", operand);
            returnCode = ifeq(&stack);
            // If top of stack is not 0 and x is positive
            if (returnCode == 1 && operand > 0) {
                i+=operand; // Skip forward 'x' steps
            } else if (returnCode == 1 && operand < 0) {
                i-=operand; // Go backwards 'x' steps
            } else if (returnCode == 0){
                // Do nothing, skip to next instruction
            }
        }
        else if (strncmp(lines[i], "igoto", 5) == 0)
        {
            operand = atoi(lines[i+1]);
            printf("igoto's operand: %d\n", operand);
            returnCode = igoto(&stack, operand);
            // If x is positive, skip 'x' instructions
            if (returnCode == 1) 
            {
                i+=operand;
            }
            // If x is negative, go back 'x' instructions
            else if (returnCode == 0) {
                i-=operand;
            }
            else {
                // Do nothing
            }
        }
        else if (strncmp(lines[i], "ireturn", 7) == 0) 
        {
            printf("%d: is the top value on the stack\n\n", ireturn(&stack));

        }
        else if (strncmp(lines[i], "imul", 4) == 0) {
            returnValue = imul(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else if (strncmp(lines[i], "idiv", 4) == 0) {
            returnValue = idiv(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else if (strncmp(lines[i], "ineg", 4) == 0) {
            returnValue = ineg(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
         else if (strncmp(lines[i], "ior", 3) == 0) {
            returnValue = ior(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else if (strncmp(lines[i], "idec", 4) == 0) {
            returnValue = idec(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else if (strncmp(lines[i], "iinc", 4) == 0) {
            returnValue = iinc(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else if (strncmp(lines[i], "iadd", 4) == 0) {
            returnValue = iadd(&stack);
            printf("%d, has been pushed onto the stack\n\n", returnValue);
        }
        else {
            // do nothing, this is for when the next line is an operand for
            // the previous instruction
            printf("(This instruction is an operand for a function)\n\n");
        }
    }
}
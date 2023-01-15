#include <stdio.h>
#include <stdlib.h> //memory allocation purposes
#include <string.h> // used for strncpy()

//defining int and string type (0 or 1)
#define INTEGER_TYPE 0
#define STRING_TYPE 1

typedef struct MixedStack_elm {
    int type; // 0 for integer, 1 for string
    union {
        int int_value;
        char string_value[64]; // 64 character string value
    } value;
    struct MixedStack_elm *next;  // Pointer to the next element in the stack
} MixedStack_elm;

typedef struct {
    int type; // 0 for integer, 1 for string
    MixedStack_elm *top;  // pointer to the top element in the stack
    int size; // number of elements in the stack
} MixedStack;

// Create a new mixed stack and allocate memory resources [initMixedStack]
void initMixedStack(MixedStack *stack);

// Destroy an existing mixed stack and release memory resources [deinitMixedStack]
void deinitMixedStack(MixedStack *stack);

// Add an element of some type on top of the mixed stack [push]
void push(MixedStack *stack, int type, void *value);

// Remove and return the element on top of the mixed stack [pop]
MixedStack_elm *pop(MixedStack *stack);

// Returns the top element on the stack without removing it [peek]
MixedStack_elm *peek(MixedStack *stack);

// Removes all elements from the stack [clear]
void clear(MixedStack *stack);

// Returns the number of elements currently stored in the stack [count]
int count(MixedStack *stack);

// Returns "yes"" if the stack is empty, "no" otherwise [isEmpty]
char *isEmpty(MixedStack *stack);

// Returns true if no more memory resources can be allocated for the stack, false otherwise [isFull]
int isFull();

// export the stack to a text file [export] [TASK2QB]
void export(MixedStack *stack, void (*int_decoder)(void *, char *), void (*string_decoder)(void *, char *), char *filename);
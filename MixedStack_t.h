#include <stdio.h>
#include <stdlib.h>

#define INTEGER_TYPE 0
#define STRING_TYPE 1
#define STACK_SIZE_LIMIT 100

typedef struct MixedStack_elm {
    int type; // 0 for integer, 1 for string
    union {
        int int_value;
        char string_value[64];
    } value;
    struct MixedStack_elm *next;
} MixedStack_elm;

typedef struct {
    int type; // 0 for integer, 1 for string
    MixedStack_elm* top;
    int size;
    union {
        int int_value;
        char string_value[64];
    } value;
} MixedStack;


// Create a new mixed stack and allocate memory resources
void initMixedStack(MixedStack* stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Destroy an existing mixed stack and release memory resources
void deinit_MixedStack(MixedStack* stack) {
    MixedStack_elm* node = stack->top;
    while (node != NULL) {
        MixedStack_elm* temp = node;
        node = node->next;
        free(temp);
    }
    stack->top = NULL;
    stack->size = 0;
}

// Add an element of some type on top of the mixed stack
void push(MixedStack* stack, int type, void* value) {
    if(stack->size == STACK_SIZE_LIMIT) {
        printf("Stack Overflow ERROR!");
        return;
    }
    MixedStack_elm* new_node = (MixedStack_elm*)malloc(sizeof(MixedStack_elm));
    new_node->type = type;
    if (type == INTEGER_TYPE) {
        new_node->value.int_value = *(int*)value;
    } else {
        snprintf(new_node->value.string_value, 64, "%s", (char*)value);
    }
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

// Remove and return the element on top of the mixed stack
MixedStack_elm* pop(MixedStack* stack) {
    if (stack->top == NULL) {
        printf("Stack Underflow!");
        return NULL;
    }
    MixedStack_elm* top = stack->top;
    stack->top = top->next;
    stack->size--;
    return top;
}

// Returns the top element on the stack without removing it
MixedStack_elm* peek(MixedStack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty!");
        return NULL;
    }
    return stack->top;
}

// Removes all elements from the stack
void clear(MixedStack* stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}

// Returns the number of elements currently stored in the stack
int count(MixedStack* stack) {
    return stack->size;
}

// Returns true if the stack is empty, false otherwise
int isEmpty(MixedStack* stack) {
    return stack->size == 0;
}

// Returns true if no more memory resources can be allocated for the stack, false otherwise
int isFull(MixedStack* stack) {
    return stack->size == STACK_SIZE_LIMIT;
}
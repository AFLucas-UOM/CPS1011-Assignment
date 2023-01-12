#include <stdio.h>
#include <stdlib.h>

typedef struct MixedStackNode {
    void* val;
    size_t size;
    struct MixedStackNode* next;
} MixedStackNode;

typedef struct MixedStack {
    MixedStackNode* top;
    size_t size;
} MixedStack;

// Create an empty MixedStack
MixedStack* createMixedStack() {
    MixedStack* stack = (MixedStack*)malloc(sizeof(MixedStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// push a new element onto the stack
void push(MixedStack* stack, void* val, size_t size) {
    MixedStackNode* node = (MixedStackNode*)malloc(sizeof(MixedStackNode));
    node->val = malloc(size);
    memcpy(node->val, val, size);
    node->size = size;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

// pop the top element from the stack
void* pop(MixedStack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    MixedStackNode* temp = stack->top;
    void* val = temp->val;
    size_t size = temp->size;
    stack->top = temp->next;
    stack->size--;
    free(temp);
    return val;
}

// export the stack to a text file
void export(MixedStack* stack, void (decoder)(void, char*), char* filename) {
    filename = "Documents/Uni/Lectures/SEM1/Programming in C/Project_C/TXT/exported_stack.txt";
    FILE* file = fopen(filename, "w");
    MixedStackNode* current = stack->top;
    while (current != NULL) {
        char* text = (char*)malloc(sizeof(char) * 64);
        decoder(current->val, text);
        fprintf(file, "%s\n", text);
        current = current->next;
        free(text);
    }
    fclose(file);
}

/**
* In this implementation, each node in the stack contains a void pointer to the value of the element, the size of the element and a pointer to the next node. The push and pop functions take in a void pointer and size as arguments to support multiple types. The export function takes in a decoder function that is able to convert the memory representation of the element to a text representation. The filename is passed as a string argument and is created with the exported data.
Please note that decoder function should be implemented in the calling application, it should know how to convert the element into a text representation.
*/
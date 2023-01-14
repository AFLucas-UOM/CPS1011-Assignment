#include <stdio.h>
#include <stdlib.h>
#include <string.h> // used for strncpy()

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

// Create a new mixed stack and allocate memory resources [initMixedStack]
void initMixedStack(MixedStack* stack) {
    // Allocate memory for the new stack
    stack->top = (MixedStack_elm*) malloc(sizeof(MixedStack_elm));
    if(stack->top == NULL)
    {
        printf("Error: Failed to allocate memory for the stack!!");
        return;
    }
    // Initialize the stack properties
    stack->top = NULL;
    stack->size = 0;
}

// Destroy an existing mixed stack and release memory resources [deinitMixedStack]
void deinitMixedStack(MixedStack* stack) {
    // Traverse the stack and free each element
    MixedStack_elm* current = stack->top;
    while (current != NULL) {
        MixedStack_elm* temp = current;
        current = current->next;
        free(temp);
    }
    // Reset the stack properties
    stack->top = NULL;
    stack->size = 0;
}

// Add an element of some type on top of the mixed stack [push]
void push(MixedStack* stack, int type, void* value) {
    if (stack->size == STACK_SIZE_LIMIT) {
        printf("Error: Stack overflow!!");
        return;
    }
    // Allocate memory for the new element
    MixedStack_elm* new_element = (MixedStack_elm*)malloc(sizeof(MixedStack_elm));

    // Check for NULL pointer
    if(new_element == NULL)
    {
        printf("Error: Failed to allocate memory for the new element!!");
        return;
    }
    // Set the element properties STRING_TYPE 1
    new_element->type = type;
    if (type == INTEGER_TYPE) {
        new_element->value.int_value = *(int*)value;
    } else if(type == STRING_TYPE) {
        strncpy(new_element->value.string_value, (char*)value, 64); // copy the string value to the stack element
    }
    new_element->next = stack->top;

    // Add the new element to the top of the stack
    stack->top = new_element;
    stack->size++;
}

// Remove and return the element on top of the mixed stack [pop]
MixedStack_elm* pop(MixedStack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack underflow!!");
        return NULL;
    }
    // Get the element on top of the stack
    MixedStack_elm* top_element = stack->top;

    // Update the top pointer and stack size
    stack->top = top_element->next;
    stack->size--;

    return top_element;
}

// Returns the top element on the stack without removing it [peek]
MixedStack_elm* peek(MixedStack* stack) {
    if (stack->top == NULL) {
        return "Error: Stack is empty!!";

    }
    // Get the element on top of the stack
    MixedStack_elm* top_element = stack->top;
    return top_element;
}

// Removes all elements from the stack [clear]
void clear(MixedStack* stack) {
    while (stack->top != NULL) {
        // Pop all elements from the stack
        MixedStack_elm* element = pop(stack);
        free(element);
    }
}

// Returns the number of elements currently stored in the stack [count]
int count(MixedStack* stack) {
    return stack->size;
}

// Returns "yes"" if the stack is empty, "no" otherwise [isEmpty]
char* isEmpty(MixedStack* stack) {
    if (stack->top == NULL) {
        return "Yes!!";
    } else {
        return "NO!!";
    }
}


// Returns true if no more memory resources can be allocated for the stack, false otherwise [isFull]
int isFull(MixedStack* stack) {
    return stack->size == STACK_SIZE_LIMIT;
}

// export the stack to a text file [export] [TASK2QB]
void export(MixedStack* stack, void (*int_decoder)(void*, char*), void (*string_decoder)(void*, char*), char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Failed to open file %s for writing!!", filename);
        return;
    }
    MixedStack_elm* current = stack->top;
    while (current != NULL) {
        // Decode the element value to text
        char text[64];
        if (current->type == INTEGER_TYPE) {
            int_decoder(&current->value.int_value, text);
            fprintf(file, "%s\n", text);
        } else if (current->type == STRING_TYPE) {
            string_decoder(current->value.string_value, text);
            fprintf(file, "%s\n", text);
        }
        // Move to the next element
        current = current->next;
    }
    fclose(file);
}
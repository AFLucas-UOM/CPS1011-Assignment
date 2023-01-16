#include <stdio.h>
#include <ctype.h> // to use tolower() function
#include <unistd.h> // to be able to use sleep function
#include <stdbool.h>// to use boolean
#include <string.h> // to use strcspn
#include "MixedStack_t.h" // Link to MixedStack_t.h

// Create a new mixed stack and allocate memory resources [initMixedStack]
void initMixedStack(MixedStack *stack) {
    // Allocate memory for the new stack
    stack->top = (MixedStack_elm *) malloc(sizeof(MixedStack_elm));
    //Error
    if (stack->top == NULL) {
        printf("Error: Failed to allocate memory for the stack!!");
        return;
    }
    // Initialize the stack properties
    stack->top = NULL;
    stack->size = 0;
}

// Destroy an existing mixed stack and release memory resources [deinitMixedStack]
void deinitMixedStack(MixedStack *stack) {
    // Traverse the stack and free each element
    MixedStack_elm *current = stack->top;
    while (current != NULL) {
        MixedStack_elm *temp = current; // create a temporary pointer to the current element
        current = current->next; // move to next element
        free(temp); // free memory of the current element
    }
    // Reset the stack properties
    stack->top = NULL;
    stack->size = 0;
}

// Add an element of some type on top of the mixed stack [push]
void push(MixedStack *stack, int type, void *value) {
    // Allocate memory for the new element
    MixedStack_elm *new_element = (MixedStack_elm *) malloc(sizeof(MixedStack_elm));
    // Check for NULL pointer
    if (new_element == NULL) {
        printf("Error: Failed to allocate memory for the new element!!");
        return;
    }
    new_element->type = type;//set the type of the element
    // TYPE: INTEGER_TYPE
    if (type == INTEGER_TYPE) {
        new_element->value.int_value = *(int *) value;// assign int value to the element
        // TYPE: STRING_TYPE
    } else if (type == STRING_TYPE) {
        strncpy(new_element->value.string_value, (char *) value, 64); // copy the string value to the stack element
    }
    new_element->next = stack->top; // set the next element to the top of the stack

    // Add the new element to the top of the stack
    stack->top = new_element;
    stack->size++; // increase the size of the stack
}

// Remove and return the element on top of the mixed stack [pop]
MixedStack_elm *pop(MixedStack *stack) {
    // check if stack is empty
    if (stack->top == NULL) {
        printf("Error: Stack underflow!!");
        return NULL;
    }
    // Get the element on top of the stack
    MixedStack_elm *top_element = stack->top;

    // Update the top pointer and stack size
    stack->top = top_element->next; // set top pointer to the next element
    stack->size--; // decrease the size of the stack
    return top_element;
}

// Returns the top element on the stack without removing it [peek]
MixedStack_elm *peek(MixedStack *stack) {
    // check if stack is empty
    if (stack->top == NULL) {
        return "Error: Stack empty!!";
    }

    // Get the element on top of the stack
    MixedStack_elm *top_element = stack->top; // create a pointer to the top element
    return top_element; // return the top element in stack
}

// Removes all elements from the stack [clear]
void clear(MixedStack *stack) {
    // check if stack is empty
    while (stack->top != NULL) {
        // Pop all elements from the stack
        MixedStack_elm *element = pop(stack); // pop the top element of the stack
        free(element); // free the memory allocated for the element
    }
}

// Returns the number of elements currently stored in the stack [count]
int count(MixedStack *stack) {
    return stack->size; // return size of Stack
}

// Returns "yes"" if the stack is empty, "no" otherwise [isEmpty]
char *isEmpty(MixedStack *stack) {
    // check if stack is empty
    if (stack->top == NULL) {
        return "Yes!!"; // return "Yes" (if stack is empty)
    } else {
        return "NO!!"; // return "NO" (if stack is not empty)
    }
}

// Returns true if no more memory resources can be allocated for the stack, false otherwise [isFull]
int isFull() {
    // Attempt to allocate memory for a new element --> check is full
    MixedStack_elm *new_element = (MixedStack_elm *) malloc(sizeof(MixedStack_elm));
    if (new_element == NULL) { // Check if the allocation was successful
        return 1; // Stack FULL
    }
    free(new_element); // Free the newly allocated memory
    return 0; // Stack NOT full
}

// export the stack to a text file [export] [TASK2QB]
void export(MixedStack *stack, void (*int_decoder)(void *, char *), void (*string_decoder)(void *, char *), char *filename) {
    FILE *file = fopen(filename, "w");// open file in MODE: writing
    // in case of error
    if (file == NULL) {
        printf("Error: Failed to open file %s for writing!!", filename);
        return;
    }
    MixedStack_elm *current = stack->top;
    while (current != NULL) {
        // Decode the element value to text
        char text[64];
        //TYPE: Int
        if (current->type == INTEGER_TYPE) {
            int_decoder(&current->value.int_value, text); // Decode integer value
            fprintf(file, "%s\n", text); // write to file
            //TYPE: String
        } else if (current->type == STRING_TYPE) {
            string_decoder(current->value.string_value, text); // Decode string value
            fprintf(file, "%s\n", text); // write to file
        }
        // Move to the next element
        current = current->next;
    }
    fclose(file); // close the file
}
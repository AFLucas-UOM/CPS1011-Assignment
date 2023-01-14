#include <stdio.h>
#include "MixedStack_t.h" // Link to MixedStack_t.h

//decoder
void int_decoder(void* value, char* buffer) {
    sprintf(buffer, "%d", *(int*)value); // convert int value to string and store it in the buffer
}
void string_decoder(void* value, char* buffer) {
    strncpy(buffer, (char*)value, 64); // copy the string value to the buffer
}

// Main() Function
int main() {
    // Create a new mixed stack
    MixedStack stack;
    initMixedStack(&stack);

    //pre-defined Testing Values --> can be user input
    // Test push() function for int
    int value1 = 101;
    push(&stack, INTEGER_TYPE, &value1);
    int value2 = 26;
    push(&stack, INTEGER_TYPE, &value2);
    int value3 = 21;
    push(&stack, INTEGER_TYPE, &value3);
    int value4 = 2023;
    push(&stack, INTEGER_TYPE, &value4);
    // Test push() function for String
    char value5[] = "my string test";
    push(&stack, STRING_TYPE, value5);

    // Test export() function NOT WORKING ATM
    const char filename[] = "exported_stack.txt";
    if (stack.top->type == INTEGER_TYPE) {
        export(&stack, int_decoder, filename);
    } else if(stack.top->type == STRING_TYPE) {
        export(&stack, string_decoder, filename);
    }

    // Test isEmpty() function
    char* is_empty = isEmpty(&stack);
    printf("Is stack empty? %s\n", is_empty);

    // Check if the stack is full
    if (isFull(&stack)) {
        printf("Stack is currently full\n");
    } else {
        printf("Stack is not currently full\n");
    }

    // Test count() function
    int stack_size = count(&stack);
    printf("Current Stack size: %d\n", stack_size);

    // Test peek() function
    MixedStack_elm* top_element = peek(&stack);
    if (top_element->type == INTEGER_TYPE) {
        printf("Top element in Stack is: %d\n", top_element->value.int_value);
    } else if (top_element->type == STRING_TYPE) {
        printf("Top element in Stack is: '%s'\n", top_element->value.string_value);
    }

    // Test pop() function
    MixedStack_elm* popped_element = pop(&stack);
    if (top_element->type == INTEGER_TYPE) {
        printf("\nPopped element: %d\n", popped_element->value.int_value);
    } else if (top_element->type == STRING_TYPE) {
        printf("\nPopped element: %s\n", popped_element->value.string_value);
    }

    // Test peek() function
    MixedStack_elm* top_element2 = peek(&stack);
    if (top_element2->type == INTEGER_TYPE) {
        printf("Top element: %d\n", top_element2->value.int_value);
    } else if (top_element2->type == STRING_TYPE) {
        printf("Top element: %s\n", top_element2->value.string_value);
    }else

    // Test clear() function
        clear(&stack);
    // Check if the stack is empty post Clear function
    if (isEmpty(&stack)) {
        printf("The stack is NOW empty\n");
    } else {
        printf("The stack is still not empty\n");
    }

    // Test deinitMixedStack() function
    deinitMixedStack(&stack);
    // Test isEmpty() function again post deinitMixedStack() function
    if (isEmpty(&stack)) {
        printf("The stack is NOW empty\n");
    } else {
        printf("The stack is still not empty\n");
    }
    return 0;
}